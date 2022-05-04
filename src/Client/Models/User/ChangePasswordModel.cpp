#include "ChangePasswordModel.h"

Net::Request ChangePasswordModel::FormRequest(const PasswordUpdate& dto, const IdType user_id)
{
	Net::Request request;
	request.uid = user_id;
	request.uri = m_hostname + "/change-password";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}

Token ChangePasswordModel::ParseResponse(const Net::Response& response)
{
	return m_parser.Parse(response.json_payload.object());
}
