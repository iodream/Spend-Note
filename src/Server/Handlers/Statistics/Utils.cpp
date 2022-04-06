#include "Utils.h"

const std::string DAILY = "daily";
const std::string WEEKLY = "weekly";
const std::string MONTHLY = "monthly";
const std::string YEARLY= "yearly";

const std::string INCOMES = "incomes";
const std::string EXPENSES= "expenses";

const std::string PER_CATEGORY = "per-category";
const std::string PERCENTAGE_PER_CATEGORY = "percentage-per-category";
const std::string PER_DAY = "per-day";

std::optional<db::Period> ToPeriod (const std::string& period) {
	if (period == DAILY)
		return db::Period::Daily;
	else if (period == WEEKLY)
		return db::Period::Weekly;
	else if (period == MONTHLY)
		return db::Period::Monthly;
	else if (period == YEARLY)
		return db::Period::Yearly;

	return std::nullopt;
}

std::optional<Type> ToType (const std::string& type) {
	if (type == INCOMES)
		return Type::Incomes;
	if (type == EXPENSES)
		return Type::Expenses;

	return std::nullopt;
}

std::optional<Format> ToFormat (const std::string& format) {
	if (format == PER_CATEGORY)
		return Format::PerCategory;
	if (format == PERCENTAGE_PER_CATEGORY)
		return Format::PercentagePerCategory;
	if (format == PER_DAY)
		return Format::PerDay;

	return std::nullopt;
}
