#pragma once

#include "Server/Handlers/AuthorizedHandler.h"

class GetIncomesHandler : public AuthorizedHandler
{
public:
	class JSONFormatter
	{
	public:
		struct Income
		{
			db::IdType income_id;
			db::IdType user_id;
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
	JSONFormatter::Incomes Map(const std::vector<db::Income>& incomes);
	JSONFormatter::Income MapIncome(const db::Income& income);

	JSONFormatter m_formatter{};
};
