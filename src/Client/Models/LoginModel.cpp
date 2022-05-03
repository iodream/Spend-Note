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
	json["email"] = credentials.email.c_str();
	json["password"] = credentials.password.c_str();
	return QJsonDocument(json);
}

void LoginModel::JSONParser::Parse(QJsonObject json, UserData& dto)
{
	SafeReadString(json, "token", dto.token);
	SafeReadId(json, "id", dto.id);
}

LoginModel::JSONParser::UserData LoginModel::ParseResponse(const Net::Response& response)
{
	JSONParser::UserData token;

	m_parser.Parse(response.json_payload.object(), token);

	return token;
}
