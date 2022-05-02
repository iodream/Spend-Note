#pragma once

#include "Entities.h"

#include "Net/Tools/Parsers/Income/IncomeCategoryJSONParserBase.h"
#include "Net/Tools/Parsers/Income/IncomeJSONParserBase.h"
#include "Net/Tools/Parsers/Income/IncomeIdJSONParser.h"
#include "Net/Tools/Parsers/Income/IncomeCategoryIdJSONParser.h"

#include "Net/Tools/Parsers/List/ListJSONParserBase.h"
#include "Net/Tools/Parsers/List/ListStateJSONParserBase.h"
#include "Net/Tools/Parsers/List/ListIdJSONParser.h"

#include "Net/Tools/Parsers/Product/ProductCategoryJSONParserBase.h"
#include "Net/Tools/Parsers/Product/ProductJSONParserBase.h"
#include "Net/Tools/Parsers/Product/ProductIdJSONParser.h"
#include "Net/Tools/Parsers/Product/ProductCategoryIdJSONParser.h"

#include "Net/Tools/Parsers/Statistics/BalanceJSONParser.h"
#include "Net/Tools/Parsers/Statistics/StatisticPerCategoryJSONParser.h"
#include "Net/Tools/Parsers/Statistics/StatisticPercentagePerCategoryJSONParser.h"
#include "Net/Tools/Parsers/Statistics/StatisticPerDayJSONParserBase.h"

#include "Net/Tools/Parsers/User/EmailUpdateJSONParser.h"

#include "Net/Tools/Parsers/ArrayJSONParserBase.h"

using IncomeCategoryJSONParser =
	IncomeCategoryJSONParserBase<IncomeCategory>;
using IncomeJSONParser =
	IncomeJSONParserBase<IncomeCategoryJSONParserBase, Income>;
using IncomesJSONParser =
	ArrayJSONParserBase<IncomeJSONParser, Income>;
using IncomeCategoriesJSONParser =
	ArrayJSONParserBase<IncomeCategoryJSONParser, IncomeCategory>;

using ListStateJSONParser =
	ListStateJSONParserBase<ListState>;
using ListJSONParser =
	ListJSONParserBase<ListStateJSONParserBase, List>;
using ListsJSONParser =
	ArrayJSONParserBase<ListJSONParser, List>;
using ListStatesJSONParser =
	ArrayJSONParserBase<ListStateJSONParser, ListState>;

using ProductCategoryJSONParser =
	ProductCategoryJSONParserBase<ProductCategory>;
using ProductJSONParser =
	ProductJSONParserBase<ProductCategoryJSONParserBase, Product>;
using ProductsJSONParser =
	ArrayJSONParserBase<ProductJSONParser, Product>;
using ProductCategoriesJSONParser =
	ArrayJSONParserBase<ProductCategoryJSONParser, ProductCategory>;

using StatisticPerDayJSONParser =
	StatisticPerDayJSONParserBase<StatisticPerDay>;
using StatisticsPerDayJSONParser =
	ArrayJSONParserBase<StatisticPerDayJSONParser, StatisticPerDay>;
