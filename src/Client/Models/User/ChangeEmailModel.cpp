#include "ChangeEmailModel.h"

QJsonDocument ChangeEmailModel::JSONFormatter::Format(const EmailInDTO& dto)
{
	QJsonObject json;
	json["code"] = dto.code.c_str();
	json["email"] = dto.email.c_str();
	return QJsonDocument(json);
}

Net::Request ChangeEmailModel::FormRequest(const EmailInDTO& dto, const IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/change-email";
	request.uid = user_id;
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}
