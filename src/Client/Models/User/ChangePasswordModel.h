#pragma once

#include "Net/Constants.h"
#include "Net/Message.h"
#include "Entities/Entities.h"
#include "Entities/Formatters.h"
#include "Entities/Parsers.h"

class ChangePasswordModel
{
public:
	ChangePasswordModel(const std::string& hostname) : m_hostname(hostname) {}
	Net::Request FormRequest(const PasswordUpdate& dto, const IdType user_id);
	Token ParseResponse(const Net::Response& response);
private:
	PasswordUpdateJSONFormatter m_formatter{};
	TokenJSONParser m_parser{};

	const std::string& m_hostname{};
};
