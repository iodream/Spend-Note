#include <QJsonObject>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>
#include "LoginHandler.h"
#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/dbfacade.h"
#include "../Net/Parsing.h"
#include "../libdal/Exceptions/databasefailure.h"

QJsonDocument LoginHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["token"] = dto.token.c_str();
	return QJsonDocument{json};
}

LoginHandler::JSONParser::DTO LoginHandler::JSONParser::Parse(
		const QJsonDocument& playload)
{
	DTO dto;
	auto json = playload.object();

	try {
		SafeReadString(json, "login", dto.login);
		SafeReadString(json, "password", dto.passwd_hash);
	}  catch (const ParsingError& ex) {
		throw Net::BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}


Net::Response LoginHandler::Handle(Net::Request& request)
{
	using namespace std;
	if (request.method == Net::HTTP_METHOD_GET) {
		auto dto = m_parser.Parse(request.json_playload);
		std::optional<User> repo_response;
		try
		{
			DbFacade repo(DB_CONN_USER + " " + DB_CONN_HOST + " " + DB_CONN_PASS + " " + DB_CONN_DBNAME);
			repo_response=repo.GetUserByLogin(dto.login);
		}
		catch(DatabaseFailure& db_fail)
		{
			return FormErrorResponse(
				Net::NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Database Failure");
		}
		catch(...)
		{
			return FormErrorResponse(
				Net::NetError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Database connection issue");
		}
		if(!repo_response || dto.passwd_hash != repo_response->password)
					return FormErrorResponse(
			Net::NetError::Status::HTTP_UNAUTHORIZED,
			"Invalid login data");

		Poco::JWT::Token token;
		token.setType("JWT");

		token.payload().set("id", std::to_string(repo_response->id));
		token.payload().set("login", std::string(repo_response->login));

		token.setIssuedAt(Poco::Timestamp());

		Poco::JWT::Signer signer(repo_response->password);
		std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
		JSONFormatter::DTO out_dto{jwt};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		Net::NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
