#pragma once

#include <QString>

enum class UIPages
{
	LOGIN = 0,
	SIGNUP,
	MAIN,
};

enum class MainSubPages
{
	LISTS = 0,
	CREATE_LIST,
	QUICK_CREATE_PRODUCT,
	EDIT_LIST,
	VIEW_LIST,

	PRODUCTS,
	CREATE_PRODUCT,
	EDIT_PRODUCT,
	VIEW_PRODUCT,

	INCOMES,
	CREATE_INCOME,
	VIEW_INCOME,
	EDIT_INCOME,

	DAILY_LIST,
	STATISTICS,
	CATEGORIES_EDIT,
	SETTINGS
};

const QString STYLESHEET_BACKGROUND_COLOR = "background-color:";
const QString DATE_FORMAT_YYYY_MM_DD_HH_MM_SS = "yyyy-MM-dd hh:mm:ss";

const std::string STATISTIC_EXPENSES = "expenses";
const std::string STATISTIC_INCOMES = "incomes";
