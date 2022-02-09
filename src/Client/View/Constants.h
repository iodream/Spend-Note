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

	PRODUCTS,
	VIEW_PRODUCT,
	CREATE_PRODUCT,
	EDIT_PRODUCT,

	ICOMES,
	SETTINGS,
};

const QString STYLESHEET_BACKGROUND_COLOR = "background-color:";
