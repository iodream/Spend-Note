#include "Utils.h"

#include "Net/Parsing.h"

Income ParseIncome(const QJsonObject& json)
{
    Income income;

    double tmp_number;
    std::string tmp_date;
    SafeReadId(json, "income_id", income.income_id);
    SafeReadId(json, "user_id", income.user_id);
    SafeReadId(json, "category_id", income.category_id);
    SafeReadString(json, "name", income.name);

    SafeReadNumber(json, "amount", tmp_number);
    income.amount = tmp_number;

    SafeReadString(json, "add_time", income.add_time);

    SafeReadString(json, "expiration_time", tmp_date);
    income.expiration_time = (tmp_date != "")
        ? std::optional<Timestamp>{tmp_date} : std::nullopt;

    return income;
}
