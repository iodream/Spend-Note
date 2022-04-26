#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QCryptographicHash>

#include "Net/Constants.h"
#include "Net/Message.h"

class VerificationModel
{
public:
	struct VerificationInDTO
	{
		std::string email;
		std::string code;

	};

	class JSONFormatter
	{
	public:
		QJsonDocument Format(const VerificationInDTO& dto);
	};

	VerificationModel(const std::string& hostname) : m_hostname{hostname} {}
	Net::Request FormRequest(const VerificationInDTO& dto);

	bool CheckData(const VerificationInDTO& dto) const;

private:
	const std::string& m_hostname;
	JSONFormatter m_formatter{};
};
