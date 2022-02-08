#include <QJsonArray>

#include "GetIncomesHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"

GetIncomesHandler::GetIncomesHandler()
{
}

Income GetIncomesHandler::ToNetIncome(const db::Income &db_income, const db::IncomeCategory& category)
{
	SCOPED_LOGGER;
	Income income;
	income.id = db_income.id;
	income.user_id = db_income.id;
	income.name = db_income.name;
	income.category.id = category.id;
	income.category.name = category.name;
	income.amount = db_income.amount;
	income.add_time = db_income.add_time;
	income.expiration_time = (db_income.expiration_time.has_value()) ? db_income.expiration_time.value() : EMPTY_STD_STRING;

	return income;
}

Net::Response GetIncomesHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto db_incomes = m_facade->GetAllIncomes(user_id);

	std::vector<Income> incomes;
	for (const db::Income& db_income : db_incomes) {
		auto category = m_facade->GetIncomeCategoryById(db_income.category_id);
		if (!category.has_value())
		{
			throw InternalError(std::string("No income category with id:") + std::to_string(db_income.category_id));
		}
		auto income = ToNetIncome(db_income, category.value());
		incomes.push_back(income);
	}

	return FormJSONResponse(m_formatter.Format(incomes));
}
