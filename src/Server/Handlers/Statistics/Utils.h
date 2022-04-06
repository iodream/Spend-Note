#pragma once

#include <optional>
#include "../libdal/Types.h"

enum class Type
{
	Incomes,
	Expenses
};

enum class Format
{
	PerCategory,
	PercentagePerCategory,
	PerDay
};

std::optional<db::Period> ToPeriod(const std::string& period);

std::optional<Type> ToType(const std::string& type);

std::optional<Format> ToFormat(const std::string& format);
