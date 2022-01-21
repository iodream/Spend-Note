#pragma once

#include "Server/Handlers/AuthorizedHandler.h"

class GetIncomesHandler : public AuthorizedHandler
{
public:
	class JSONParser
	{
	public:
		struct DTO
		{
			IdType user_id;
		};

		DTO Parse(const QJsonDocument& token_body);
	};

	class JSONFormatter
	{
	public:
		struct DTO
		{
			std::vector<Income> incomes;
		};

		QJsonDocument Format(const DTO& dto);
	};

	GetIncomesHandler();
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};

