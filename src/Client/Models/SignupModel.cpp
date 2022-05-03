#include "SignupModel.h"
#include "Net/Parsing.h"
#include "Utils.h"
Net::Request SignupModel::FormRequest(const SignupInDTO& dto)
{
	Net::Request request;
	request.uri = m_hostname + "/signup";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}

QJsonDocument SignupModel::JSONFormatter::Format(const SignupInDTO& dto)
{
	QJsonObject json;
  json["email"] = dto.email.c_str();
	json["password"] = dto.password.c_str();
	return QJsonDocument(json);
}

//these functions return true if checks pass
bool SignupModel::CheckPassRepeat(const SignupInDTO& dto) const
{
	return (dto.password == dto.pass_repeat);
}

//checks data for presence of any characters at all
bool SignupModel::CheckData(const SignupInDTO& dto) const
{
	auto username = EraseWhitespace(dto.email);
	auto pass = EraseWhitespace(dto.password);
	return (!username.empty() && !pass.empty());
}
