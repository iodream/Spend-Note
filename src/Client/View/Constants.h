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

	EDIT_LIST,
	VIEW_LIST,

	PRODUCTS,
	CREATE_PRODUCT,
	EDIT_PRODUCT,
	VIEW_PRODUCT,

	INCOMES,
	//CREATE_INCOME,
	VIEW_INCOME,

	SETTINGS,
};

enum class ErrorCodes
{
	PASSWORDS_MISMATCH= 1,
	EMPTY_FIELD,
	UPDATE_ERROR,
};

const QString STYLESHEET_BACKGROUND_COLOR = "background-color:";
