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

QJsonDocument AuthorizedHandler::DecodeJWTTokenBody(const std::string& token)
{
	std::stringstream body_encoded;
	auto body_begin_pos = token.find(".");
	if (body_begin_pos == std::string::npos)
		throw Net::UnauthorizedError("No token body");

	body_begin_pos++;

	auto body_end_pos = token.find(".", body_begin_pos);
	if (body_end_pos == std::string::npos)
		throw Net::UnauthorizedError("No token body");

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

bool AuthorizedHandler::CheckAuthorization(const Net::Request& request)
{
	if (request.auth_scheme != Net::AUTH_SCHEME_TYPE_BEARER)
		return false;

	try {
		Poco::JWT::Signer signer(Net::DUMMY_PASSWORD);
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
				Net::NetError::Status::HTTP_UNAUTHORIZED,
				"No authorization data");
		}
		request.jwt_token_body = DecodeJWTTokenBody(request.auth_info);
	}
	else {
		return FormErrorResponse(
			Net::NetError::Status::HTTP_UNAUTHORIZED,
			"Unsupported authorization scheme");
	}


	if (!CheckAuthorization(request)) {
		return FormErrorResponse(
			Net::NetError::Status::HTTP_UNAUTHORIZED,
			"Invalid authorizaion data");
	}
	return AuthHandle(request);
}
