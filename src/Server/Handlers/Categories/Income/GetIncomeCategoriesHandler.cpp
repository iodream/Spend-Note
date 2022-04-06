#include <QJsonArray>

#include "GetIncomeCategoriesHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"

GetIncomeCategoriesHandler::GetIncomeCategoriesHandler()
{
}

Net::Response GetIncomeCategoriesHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	auto db_income_categories = m_facade->GetAllIncomeCategories(user_id);
	std::vector<IncomeCategory> income_categories;

	for (const db::IncomeCategory& db_income_category : db_income_categories) {
		auto income_category = ToNetIncomeCategory(db_income_category);
		income_categories.push_back(income_category);
	}

	return FormJSONResponse(m_formatter.Format(income_categories));
}
