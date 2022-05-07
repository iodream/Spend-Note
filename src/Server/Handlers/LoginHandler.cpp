#include <memory>

#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "Poco/DigestStream.h"
#include "Poco/MD5Engine.h"

#include "LoginHandler.h"

#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

#include "../Utils.h"

LoginHandler::LoginHandler()
{

}

void LoginHandler::UpdatePeriodicIncomes(db::IdType user_id)
{
	const auto periodic_incomes = m_facade->GetAllPeriodicIncomes(user_id);

	for (const auto& periodic_income : periodic_incomes) {
		while (m_facade->CanGeneratePeriodicIncome(user_id, periodic_income.id)) {
			// Generate income
			db::Income income;
			income.id = 0;
			income.user_id = user_id;
			income.category_id = periodic_income.category_id;
			income.name = periodic_income.name;
			income.amount = periodic_income.amount;
			income.add_time = QDateTime::currentDateTime().toString(Qt::ISODate).toStdString();
			income.expiration_time = std::nullopt;

			m_facade->AddIncome(income);
			m_facade->UpdatePeriodicIncome(periodic_income);
		}
	}
}

QJsonDocument LoginHandler::JSONFormatter::Format(const OutDto& dto)
{
	SCOPED_LOGGER;
	QJsonObject json;
	json["token"] = dto.token.c_str();
	json["id"] = dto.id;
	return QJsonDocument{json};
}

LoginHandler::JSONParser::Login LoginHandler::JSONParser::Parse(
		const QJsonDocument& payload)
{
	SCOPED_LOGGER;
	Login dto;
	auto json = payload.object();

	try {
		SafeReadString(json, "login", dto.login);
		SafeReadString(json, "password", dto.password);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response LoginHandler::Handle(Net::Request& request)
{
	SCOPED_LOGGER;
	auto dto = m_parser.Parse(request.json_payload);
	auto user = m_facade->GetUserByLogin(dto.login);

	dto.password_hash = HashingPassword(dto.password, user->salt);

	if(!user || dto.password_hash != user->password_hash) {
		return FormErrorResponse(
		NetError::Status::HTTP_UNAUTHORIZED,
		"Invalid login data");
	}

	Poco::JWT::Token token;
	token.setType("JWT");

	token.payload().set("id", FormatId(user->id));
	token.payload().set("login", std::string(user->login));

	token.setIssuedAt(Poco::Timestamp());

	Poco::JWT::Signer signer(user->password_hash);
	std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
	JSONFormatter::OutDto out_dto{jwt, user->id};

	UpdatePeriodicIncomes(user->id);

	return FormJSONResponse(m_formatter.Format(out_dto));
}
