#include "LoginModel.h"
#include "Net/Parsing.h"

Net::Request LoginModel::FormRequest(LoginInDTO dto)
{
	Net::Request request;
	request.uri = "http://localhost:8080/login";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_playload = m_formatter.Format(dto);
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

LoginOutDTO LoginModel::ParseResponse(const Net::Response& response)
{
    LoginOutDTO dto;

	m_parser.Parse(response.json_playload.object(), dto);

	return dto;
}
