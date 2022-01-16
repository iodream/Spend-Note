#include "LoginModel.h"

#include "Net/Parsing.h"

Net::Request LoginModel::FormRequest(LoginInDTO dto)
{
	Net::Request request;
	request.uri = "http://localhost:8080/fake_login";
	request.method = Net::HTTP_METHOD_GET;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_playload = m_formatter.Format(dto);
	return request;
}


QJsonDocument LoginModel::JSONFormatter::Format(const LoginInDTO& dto)
{
	QJsonObject json;

    QByteArray encrypted_password = QByteArray::fromStdString(dto.password);
    encrypted_password = QCryptographicHash::hash(encrypted_password, QCryptographicHash::Sha1);

    json.insert("login", QString::fromStdString(dto.login));
    json.insert("password", QString(encrypted_password));

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
