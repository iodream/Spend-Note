#include "AddVerificationModel.h"
#include "Net/Parsing.h"
#include "Utils.h"

Net::Request AddVerificationModel::FormRequest(const VerificationInDTO& dto)
{
	Net::Request request;
	request.uri = m_hostname + "/verification";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}

QJsonDocument AddVerificationModel::JSONFormatter::Format(const VerificationInDTO& dto)
{
	QJsonObject json;
	json["email"] = dto.email.c_str();
	return QJsonDocument(json);
}

//checks data for presence of any characters at all
bool AddVerificationModel::CheckData(const VerificationInDTO& dto) const
{
	auto email = EraseWhitespace(dto.email);
	return (!email.empty());
}
