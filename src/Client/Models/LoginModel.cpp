#include <QCryptographicHash>

#include "LoginModel.h"
#include "Net/Parsing.h"

Net::Request LoginModel::FormRequest(JSONFormatter::LoginInDTO dto)
{
	Net::Request request;
	request.uri = m_hostname + "login";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}

QJsonDocument LoginModel::JSONFormatter::Format(const LoginInDTO& dto)
{
	QJsonObject json;
	QByteArray password = QByteArray::fromStdString(dto.password);

	json["login"] = dto.login.c_str();
	auto digest = QString(QCryptographicHash::hash(
			password, QCryptographicHash::Sha1).toHex());
	json["password"] = digest.toStdString().c_str();
    return QJsonDocument(json);
}

void LoginModel::JSONParser::Parse(QJsonObject json, LoginOutDTO& dto)
{
	SafeReadString(json, "token", dto.token);
}

LoginModel::JSONParser::LoginOutDTO LoginModel::ParseResponse(const Net::Response& response)
{
	JSONParser::LoginOutDTO dto;

	m_parser.Parse(response.json_payload.object(), dto);

	return dto;
}
