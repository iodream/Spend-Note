#include "AddIncomeHandler.h"

#include "../Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "Utils.h"

#include "../libdal/Exceptions/SQLFailure.h"
#include "Logger/ScopedLogger.h"

AddIncomeHandler::AddIncomeHandler()
{
}

db::Income AddIncomeHandler::JSONParser::Parse(
	const QJsonDocument& json_doc)
{
	SCOPED_LOGGER;
	db::Income dto;

	auto json = json_doc.object();

	try
	{
		dto = ParseIncome(json);
	}
	catch(const ParsingError& ex)
	{
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return dto;
}

Net::Response AddIncomeHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));

	auto dto = m_parser.Parse(request.json_payload);
	dto.user_id = user_id;

	AddIncomeHandler::JSONFormatter::DTO out_dto;

	try
	{
		out_dto.income_id = m_facade->AddIncome(dto).value();
	}
	catch (const db::SQLFailure& e)
	{
		throw FormErrorResponse(
			NetError::Status::HTTP_CONFLICT,
			"Unable to create resource");
	}

	return FormJSONResponse(m_formatter.Format(out_dto));
}

QJsonDocument AddIncomeHandler::JSONFormatter::Format(const DTO& dto)
{
	SCOPED_LOGGER;
	QJsonObject json;
	json["id"] = std::to_string(dto.income_id).c_str();
	return QJsonDocument{json};
}
