#include "SignupModel.h"
#include "Net/Parsing.h"

Net::Request SignupModel::FormRequest(const SignupInDTO& dto)
{
	Net::Request request;
	request.uri = m_hostname + "signup";
	request.method = Net::HTTP_METHOD_POST;
	request.content_type = Net::CONTENT_TYPE_APPLICATION_JSON;
	request.json_payload = m_formatter.Format(dto);
	return request;
}

QJsonDocument SignupModel::JSONFormatter::Format(const SignupInDTO& dto)
{
	QJsonObject json;
	QByteArray password = QByteArray::fromStdString(dto.password);

	json["login"] = dto.login.c_str();
	auto digest = QString(QCryptographicHash::hash(
			password, QCryptographicHash::Sha1).toHex());
	json["password"] = digest.toStdString().c_str();
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
	auto username = dto.login;
	auto pass = dto.password;
	username.erase(std::remove_if(username.begin(), username.end(), ::isspace)
				   , username.end());
	pass.erase(std::remove_if(pass.begin(), pass.end(), ::isspace)
			   , pass.end());
	return (!username.empty() && !pass.empty());
}
