#include <QJsonArray>

#include "GetPeriodicIncomesHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "Utils.h"

GetPeriodicIncomesHandler::GetPeriodicIncomesHandler()
{
}

Net::Response GetPeriodicIncomesHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	if (request.uid != user_id){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get periodic incomes for user with id \"" + std::to_string(user_id) + "\"");
	}

	std::vector<db::PeriodicIncome> db_incomes;
	try {
		db_incomes = m_facade->GetAllPeriodicIncomes(user_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"User with id = " + std::to_string(user_id) + " not found");
	}

	std::vector<PeriodicIncome> incomes;
	for (auto db_income : db_incomes) {
		auto category = m_facade->GetIncomeCategoryById(db_income.category_id);
		if (!category.has_value())
		{
			throw InternalError(std::string("No income category with id:") + std::to_string(db_income.category_id));
		}
		auto income = ToNetPeriodicIncome(db_income, category.value());
		incomes.push_back(income);
	}

	return FormJSONResponse(m_formatter.Format(incomes));
}
