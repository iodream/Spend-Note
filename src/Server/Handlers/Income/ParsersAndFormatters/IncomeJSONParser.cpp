#include "IncomeJSONParser.h"

#include "../../Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Utils/IncomeUtils.h"

Income IncomeJSONParser::Parse(const QJsonDocument &json_doc)
{
	IncomeIn dto;
	auto json = json_doc.object();

	try
	{
		dto = ParseIncome(json);
	}
	catch(const ParsingError& ex)
	{
		throw BadRequestError{std::string{"Parsing Error: "}.append(ex.what())};
	}

	return ToIncome(dto);
}

Income IncomeJSONParser::ToIncome(const IncomeIn &income_in)
{
	Income income;

	income.income_id = income_in.id;
	income.category_id = income_in.category.id;
	income.name = income_in.name;
	income.amount = income_in.amount;
	income.add_time = income_in.add_time;
	income.expiration_time = (income_in.expiration_time != "")
			? std::optional<Timestamp>{income_in.expiration_time} : std::nullopt;

	return income;
}
