#include "ChangeEmailModel.h"

Net::Request ChangeEmailModel::FormRequest(const EmailUpdate& dto, const IdType user_id)
{
	Net::Request request;
	request.uri = m_hostname + "/email";
	request.uid = user_id;
	request.method = Net::HTTP_METHOD_PUT;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}
