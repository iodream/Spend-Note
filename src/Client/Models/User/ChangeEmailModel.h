#pragma once

#include "Net/Constants.h"
#include "Net/Message.h"
#include "Entities/Entities.h"
#include "Entities/Formatters.h"

class ChangeEmailModel
{
public:
	ChangeEmailModel(const std::string& hostname) : m_hostname(hostname) {}
	Net::Request FormRequest(const EmailUpdate& dto, const IdType user_id);

private:
	EmailUpdateJSONFormatter m_formatter{};

	const std::string& m_hostname{};
};
