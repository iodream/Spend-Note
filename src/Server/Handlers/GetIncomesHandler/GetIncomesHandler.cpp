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
			JSONFormatter::DTO response_dto {m_facade->GetAllIncomes(request.uid).value()};
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

QJsonDocument GetIncomesHandler::JSONFormatter::Format(const DTO& dto)
{
	QJsonArray incomes_json;
	for (const Income& income : dto.incomes)
	{
		QJsonObject income_json;
		income_json["id"] = std::to_string(income.income_id).c_str();
		income_json["user_id"] = std::to_string(income.user_id).c_str();
		income_json["name"] = income.name.c_str();
		income_json["amount"] = income.amount;
		income_json["category_id"] = income.category_id;
		income_json["add_time"] = income.add_time.c_str();
		income_json["expiration_time"] = income.expiration_time.c_str();
		incomes_json.append(income_json);
	}

	QJsonObject json;
	json["incomes"] = incomes_json;
	return QJsonDocument{json};
}
