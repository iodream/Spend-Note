#include <memory>

#include <QJsonObject>
#include <QDateTime>
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

void LoginHandler::UpdatePeriodicProducts(db::IdType user_id)
{
	const auto periodic_products = m_facade->GetPeriodicProductsForUser(user_id);

	for (const auto& periodic_product : periodic_products) {
		while (m_facade->CanPeriodicProductGenerate(periodic_product.id)) {
			// Generate product
			db::Product product;
			product.id = 0;
			product.list_id = periodic_product.list_id;
			product.category_id = periodic_product.category_id;
			product.name = periodic_product.name;
			product.price = periodic_product.price;
			product.amount = periodic_product.amount;
			product.product_priority = periodic_product.product_priority;
			product.is_bought = false;
			product.add_date = QDateTime::currentDateTime().toString(Qt::ISODate).toStdString();
			product.purchase_date = std::nullopt;
			product.buy_until_date = std::nullopt;
			product.periodic_id = periodic_product.id;

			m_facade->AddProduct(product);
			m_facade->UpdatePeriodicProductAddNext(periodic_product);
		}
	}
}

LoginHandler::LoginHandler()
{

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

	UpdatePeriodicProducts(user->id);

	return FormJSONResponse(m_formatter.Format(out_dto));
}
