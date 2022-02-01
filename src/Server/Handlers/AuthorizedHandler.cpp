#include <QJsonObject>

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"
#include "Poco/JWT/JWTException.h"

#include "Poco/StreamCopier.h"

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"

#include "AuthorizedHandler.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Common.h"
#include "Net/Parsing.h"

AuthorizedHandler::AuthorizedHandler(IDbFacade::Ptr facade)
	: ICommandHandler(std::move(facade))
{

}

QJsonDocument AuthorizedHandler::DecodeJWTTokenBody(const std::string& token)
{
	std::stringstream body_encoded;
	auto body_begin_pos = token.find(".");
	if (body_begin_pos == std::string::npos)
		throw UnauthorizedError("No token body");

	body_begin_pos++;

	auto body_end_pos = token.find(".", body_begin_pos);
	if (body_end_pos == std::string::npos)
		throw UnauthorizedError("No token body");

	auto body_size = body_end_pos - body_begin_pos;

	auto tmp = token.substr(body_begin_pos, body_size);

	body_encoded << token.substr(body_begin_pos, body_size);

	Poco::Base64Decoder decoder_stream{
		body_encoded,
		Poco::BASE64_URL_ENCODING | Poco::BASE64_NO_PADDING};

	std::string _raw_token_body{std::istreambuf_iterator{decoder_stream}, {}};

	auto raw_token_body = QByteArray::fromRawData(
		_raw_token_body.data(),
		_raw_token_body.size());

	return QJsonDocument::fromJson(raw_token_body);
}

AuthorizedHandler::JSONParser::Token AuthorizedHandler::JSONParser::Parse(
	const QJsonDocument& payload)
{
	Token dto;
	auto json = payload.object();

	try {
		SafeReadId(json, "id", dto.id);
		SafeReadString(json, "login", dto.login);
		SafeReadNumber(json, "iat", dto.iat);
	}  catch (const ParsingError& ex) {
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

bool AuthorizedHandler::CheckAuthorization(Net::Request& request)
{
	if (request.auth_scheme != Net::AUTH_SCHEME_TYPE_BEARER)
		return false;
	auto parsed_token = m_parser.Parse(request.jwt_token_body);
	auto user = m_facade->GetUserById(parsed_token.id);
	if(!user)
		return false;
	auto password = user->password;
	request.uid = user->id;
	try {
		Poco::JWT::Signer signer(password);
		Poco::JWT::Token token = signer.verify(request.auth_info);
	}
	catch (const Poco::JWT::SignatureVerificationException& ex) {
		return false;
	}
	return true;
}

Net::Response AuthorizedHandler::Handle(Net::Request& request)
{
	if (request.auth_scheme == Net::AUTH_SCHEME_TYPE_BEARER) {
		if (!request.auth_info.size()) {
			return FormErrorResponse(
				NetError::Status::HTTP_UNAUTHORIZED,
				"No authorization data");
		}
		request.jwt_token_body = DecodeJWTTokenBody(request.auth_info);
	}
	else {
		return FormErrorResponse(
			NetError::Status::HTTP_UNAUTHORIZED,
			"Unsupported authorization scheme");
	}


	if (!CheckAuthorization(request)) {
		return FormErrorResponse(
			NetError::Status::HTTP_UNAUTHORIZED,
			"Invalid authorizaion data");
	}
	return AuthHandle(request);
}
