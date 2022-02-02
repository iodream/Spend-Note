#include "GetIncomesHandler.h"

#include <QJsonArray>
#include <QJsonObject>

#include "../libdal/Exceptions/SQLFailure.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"

GetIncomesHandler::GetIncomesHandler()
{

}

Net::Response GetIncomesHandler::AuthHandle(const Net::Request& request)
{
	Q_UNUSED(request);
	try
	{

		auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
		JSONFormatter::DTO response_dto {Map(m_facade->GetAllIncomes(user_id))};
		return FormJSONResponse(m_formatter.Format(response_dto));
	}
	catch (const SQLFailure& e)
	{
		return FormErrorResponse(
			InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
			"Failed to retrieve incomes from database");

	}
}

Incomes GetIncomesHandler::Map(const std::vector<Income>& incomes)
{
	Incomes incomes_out;
	incomes_out.reserve(incomes.size());
	for (const auto& income : incomes)
	{
		incomes_out.push_back(MapIncome(income));
	}
	return incomes_out;
}

IncomeOut GetIncomesHandler::MapIncome(const Income& income)
{
	IncomeOut income_out;


	income_out.income_id = income.id;
	income_out.user_id = income.user_id;

	income_out.name = income.name;
	income_out.amount = income.amount;
	auto category_name = m_facade->GetIncomeCategoryById(income.category_id);
	if (category_name)
	{
		income_out.category_name = category_name.value().name;
	}
	else
	{
		throw BadRequestError{std::string{"Referenced nonexistent category with id "} + std::to_string(income.category_id)};
	}
	income_out.add_time = income.add_time;
	income_out.expiration_time = income.expiration_time.value_or("");

	return income_out;
}
