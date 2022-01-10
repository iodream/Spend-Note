#include <QJsonObject>

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"
#include "Poco/JWT/JWTException.h"

#include "Poco/StreamCopier.h"

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"

#include "AuthorizedHandler.h"
#include "Net/Error.h"

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

void AuthorizedHandler::CheckAuthorization(const Net::Request& request)
{
	if (request.auth_scheme != Net::AUTH_SCHEME_TYPE_BEARER)
		throw Net::UnauthorizedError("Unsupported authorization scheme");

	try {
		Poco::JWT::Signer signer("0123456789ABCDEF0123456789ABCDEF");
		Poco::JWT::Token token = signer.verify(request.auth_info);
	}
	catch (const Poco::JWT::SignatureVerificationException& ex) {
		throw Net::UnauthorizedError("Invalid token");
	}
}

Net::Response AuthorizedHandler::Handle(Net::Request& request)
{
	if (request.auth_scheme == Net::AUTH_SCHEME_TYPE_BEARER)
        request.jwt_token_body = DecodeJWTTokenBody(request.auth_info);
	CheckAuthorization(request);
	return AuthHandle(request);
}
