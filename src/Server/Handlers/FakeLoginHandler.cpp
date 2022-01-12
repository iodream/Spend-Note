#include <QJsonObject>

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"

#include "Server/Error.h"
#include "FakeLoginHandler.h"
#include "Common.h"

QJsonDocument FakeLoginHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["token"] = dto.token.c_str();
	return QJsonDocument{json};
}

Net::Response FakeLoginHandler::Handle(Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET) {
		Poco::JWT::Token token;
		token.setType("JWT");
		token.payload().set("user", std::string("Admin"));
		token.setIssuedAt(Poco::Timestamp());

		Poco::JWT::Signer signer(Net::DUMMY_PASSWORD);
		std::string jwt = signer.sign(token, Poco::JWT::Signer::ALGO_HS256);
		JSONFormatter::DTO out_dto{jwt};
		return FormJSONResponse(m_formatter.Format(out_dto));
	}
	throw Net::BadRequestError("Unsupported method");
}
