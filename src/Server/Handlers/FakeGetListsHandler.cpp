#include <QJsonObject>

#include "FakeGetListsHandler.h"
#include "../ClientError.h"

#include "Poco/JWT/Token.h"
#include "Poco/JWT/Signer.h"
#include "Poco/JWT/JWTException.h"
#include "Poco/StreamCopier.h"

#include "Poco/Base64Encoder.h"
#include "Poco/Base64Decoder.h"


FakeGetListsHandler::InDTO FakeGetListsHandler::Parser::Parse(const QJsonDocument& json_doc)
{
	InDTO dto;
	auto json = json_doc.object();

	if (json.contains("token") && json["token"].isString()) {
		dto.token = json["token"].toString().toStdString();
	}
	else {
		throw BadRequestError{"Failed to parse \"token_body\" field"};
	}

	std::stringstream token_body_encoded;
	auto token_body_begin_pos = dto.token.find(".") + 1;
	auto token_body_size = dto.token.find(".", token_body_begin_pos) - token_body_begin_pos;
	token_body_encoded << dto.token.substr(token_body_begin_pos, token_body_size);

	Poco::Base64Decoder decoder_stream{
				token_body_encoded,
				Poco::BASE64_URL_ENCODING | Poco::BASE64_NO_PADDING};

	auto token_doc_body_raw = std::string{std::istreambuf_iterator{decoder_stream}, {}};

	auto token_body_doc = QJsonDocument::fromJson(
		QByteArray::fromRawData(token_doc_body_raw.data(), token_doc_body_raw.size())
	);

	dto.user = token_body_doc.object()["name"].toString().toStdString();

	Poco::JWT::Signer signer("0123456789ABCDEF0123456789ABCDEF");

	try {
		Poco::JWT::Token token = signer.verify(dto.token);
	}
	catch (const Poco::JWT::SignatureVerificationException& ex) {
		throw ForbiddenError(ex.what());
	}

	return dto;
}

QJsonDocument FakeGetListsHandler::Formatter::Format(const OutDTO& dto)
{
	QJsonObject json;
	json["msg"] = std::string{dto.msg}.append(dto.user).c_str();
	return QJsonDocument{json};
}

QJsonDocument FakeGetListsHandler::Handle(const QJsonDocument& json_doc)
{
	auto in_dto = m_parser.Parse(json_doc);
	OutDTO out_dto{
		in_dto.user,
		"Some lists msg for user "
	};
	return m_formatter.Format(out_dto);
}
