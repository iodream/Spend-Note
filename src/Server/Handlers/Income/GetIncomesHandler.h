#pragma once

#include "Server/Handlers/AuthorizedHandler.h"
#include "ParsersAndFormatters/IncomeJSONFormatter.h"
#include "DTO/IncomeOut.h"

class GetIncomesHandler : public AuthorizedHandler
{
public:
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

	GetIncomesHandler();
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	Incomes Map(const std::vector<Income>& incomes);
	IncomeOut MapIncome(const Income& income);

	IncomeJSONFormatter m_formatter{};
};

