#include "IncomeJSONFormatter.h"

#include "../../Common.h"
#include "Net/Parsing.h"

#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Utils/IncomeUtils.h"
#include "../Utils/IncomeIdUtils.h"

QJsonDocument IncomeJSONFormatter::Format(const IncomeId& dto)
{
	return FormatIncomeId(dto);
}

QJsonObject IncomeJSONFormatter::Format(const IncomeOut& income)
{
	return FormatIncome(income);
}

QJsonDocument IncomeJSONFormatter::Format(const Incomes& incomes)
{
	QJsonArray incomes_json;
	for (const IncomeOut& income : incomes)
	{
		incomes_json.append(Format(income));
	}

	QJsonObject json;
	json["incomes"] = incomes_json;
	return QJsonDocument{json};
}
