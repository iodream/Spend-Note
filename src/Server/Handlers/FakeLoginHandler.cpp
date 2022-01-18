#include <QJsonObject>

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"

#include "FakeLoginHandler.h"
#include "Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Repositories/userrepository.h"
#include "../Net/Parsing.h"
#include <iostream>
#include "../libdal/Exceptions/databasefailure.h"

QJsonDocument FakeLoginHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["token"] = dto.token.c_str();
	return QJsonDocument{json};
}

FakeLoginHandler::JSONParser::DTO FakeLoginHandler::JSONParser::Parse(
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


Net::Response FakeLoginHandler::Handle(Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {
		auto dto = m_parser.Parse(request.json_playload);
		//try {
		pqxx::connection conn("username=test_user"
							  "host=127.0.0.1"
							  "password=test_pass"
							  "dbname=SpendAndNote");
		//UserRepository repo(conn);
		auto repo_user=repo.GetByLogin(dto.login);
//		catch(DatabaseFailure& db_fail)
//		{
//			FormErrorResponse(Net::ServerError("Login database retrieval error",
//				Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_INTERNAL_SERVER_ERROR , Net::Response:);
//					;

//		}
		//add check if user exists and if pass is valid
		if(!repo_user || repo_user->password != dto.login)
			//authorization error return
		std::cout << repo_user->id <<std::endl;
		std::cout << repo_user->login <<std::endl;
		std::cout << repo_user->password <<std::endl;
		Poco::JWT::Token token;
		token.setType("JWT");
//		token.payload().set("id", std::string(repo_user.id));
//		token.payload().set("login", std::string(repo_user.login));
		//}

		token.setIssuedAt(Poco::Timestamp());

		Poco::JWT::Signer signer(Net::DUMMY_PASSWORD);//needs to be user passwd hash
		std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
		JSONFormatter::DTO out_dto{jwt};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	return FormErrorResponse(
		Net::NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}
