#include "GetIncomesHandler.h"

#include <QJsonArray>
#include <QJsonObject>

#include "../libdal/Exceptions/DatabaseFailure.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"

GetIncomesHandler::GetIncomesHandler()
{

}

Net::Response GetIncomesHandler::AuthHandle(const Net::Request& request)
{
	if (request.method == Net::HTTP_METHOD_GET)
	{
		try
		{
			JSONFormatter::DTO response_dto {Map(m_facade->GetAllIncomes(request.uid).value())};
			return FormJSONResponse(m_formatter.Format(response_dto));
		}
		catch (const DatabaseFailure& e)
		{
			return FormErrorResponse(
				InternalError::Status::HTTP_INTERNAL_SERVER_ERROR,
				"Failed to retrieve incomes from database");
		}
	}
	return FormErrorResponse(
		NetError::Status::HTTP_BAD_REQUEST,
		"Unsupported method");
}

GetIncomesHandler::JSONFormatter::Incomes GetIncomesHandler::Map(std::vector<Income> incomes)
{
	JSONFormatter::Incomes incomes_out;
	incomes_out.reserve(incomes.size());
	for (const auto& income : incomes)
	{
		incomes_out.push_back(MapIncome(income));
	}
	return incomes_out;
}

GetIncomesHandler::JSONFormatter::Income GetIncomesHandler::MapIncome(Income income)
{
	JSONFormatter::Income income_out;

	income_out.income_id = income.income_id;
	income_out.user_id = income.income_id;
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
	income_out.expiration_time = income.expiration_time; // replace with income.expiration_time.value_or("") when libdal changes merged

	return income_out;
}

QJsonObject GetIncomesHandler::JSONFormatter::Format(const Income& income)
{
	QJsonObject income_json;
	income_json["id"] = std::to_string(income.income_id).c_str();
	income_json["user_id"] = std::to_string(income.user_id).c_str();
	income_json["name"] = income.name.c_str();
	income_json["amount"] = income.amount;
	income_json["category_name"] = income.category_name.c_str();
	income_json["add_time"] = income.add_time.c_str();
	income_json["expiration_time"] = income.expiration_time.c_str();
	return income_json;
}

QJsonArray GetIncomesHandler::JSONFormatter::Format(const Incomes& incomes)
{
	QJsonArray incomes_json;
	for (const Income& income : incomes)
	{
		incomes_json.append(Format(income));
	}
	return incomes_json;
}

QJsonDocument GetIncomesHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonObject json;
	json["incomes"] = Format(dto.incomes);
	return QJsonDocument{json};
}
