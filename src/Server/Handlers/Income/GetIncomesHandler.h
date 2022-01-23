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
		struct Income
		{
			IdType income_id;
			IdType user_id;
			std::string name;
			double amount;
			std::string category_name;
			std::string add_time;
			std::string expiration_time;
		};

		using Incomes = std::vector<Income>;

		struct DTO
		{
			Incomes incomes;
		};

		QJsonObject Format(const Income& income);
		QJsonArray Format(const Incomes& incomes);
		QJsonDocument Format(const DTO& dto);
	};

	GetIncomesHandler(IDbFacade::Ptr facade);
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter::Incomes Map(const std::vector<Income>& incomes);
	JSONFormatter::Income MapIncome(const Income& income);

	JSONParser m_parser{};
	JSONFormatter m_formatter{};
};

