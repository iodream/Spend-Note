#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include "Net/Constants.h"
#include "Net/Message.h"
#include "Entities/Entities.h"

class ChangeEmailModel
{
public:
	struct EmailInDTO
	{
		std::string code;
		std::string email;
	};

	ChangeEmailModel(const std::string& hostname) : m_hostname(hostname) {}
	Net::Request FormRequest(const EmailInDTO& dto, const IdType user_id);

private:
	class JSONFormatter
	{
	public:
		QJsonDocument Format(const EmailInDTO& dto);
	} m_formatter{};

	const std::string& m_hostname{};
};
