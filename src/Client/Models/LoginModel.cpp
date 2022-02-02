#include <QCryptographicHash>

#include "LoginModel.h"
#include "Net/Parsing.h"

Net::Request LoginModel::FormRequest(JSONFormatter::Credentials credentials)
{
	Net::Request request;
	request.uri = m_hostname + "/login";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(credentials);
	return request;
}

QJsonDocument LoginModel::JSONFormatter::Format(const Credentials& credentials)
{
	QJsonObject json;
	QByteArray password = QByteArray::fromStdString(credentials.password);

	json["login"] = credentials.login.c_str();
	auto digest = QString(QCryptographicHash::hash(
			password, QCryptographicHash::Sha1).toHex());
	json["password"] = digest.toStdString().c_str();
    return QJsonDocument(json);
}

void LoginModel::JSONParser::Parse(QJsonObject json, Token& dto)
{
	SafeReadString(json, "token", dto.token);
}

LoginModel::JSONParser::Token LoginModel::ParseResponse(const Net::Response& response)
{
	JSONParser::Token token;

	m_parser.Parse(response.json_payload.object(), token);

	return token;
}
