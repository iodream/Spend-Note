#pragma once

#include "Entities.h"

#include "Net/Tools/Formatters/Income/IncomeCategoryJSONFormatterBase.h"
#include "Net/Tools/Formatters/Income/IncomeJSONFormatterBase.h"
#include "Net/Tools/Formatters/Income/IncomeIdJSONFormatter.h"
#include "Net/Tools/Formatters/Income/IncomeCategoryIdJSONFormatter.h"
#include "Net/Tools/Formatters/PeriodicIncome/PeriodicIncomeIdJSONFormatter.h"
#include "Net/Tools/Formatters/PeriodicIncome/PeriodicIncomeJSONFormatterBase.h"

#include "Net/Tools/Formatters/List/ListJSONFormatterBase.h"
#include "Net/Tools/Formatters/List/ListStateJSONFormatterBase.h"
#include "Net/Tools/Formatters/List/ListIdJSONFormatter.h"

#include "Net/Tools/Formatters/Product/ProductCategoryJSONFormatterBase.h"
#include "Net/Tools/Formatters/Product/ProductJSONFormatterBase.h"
#include "Net/Tools/Formatters/Product/ProductIdJSONFormatter.h"
#include "Net/Tools/Formatters/Product/ProductCategoryIdJSONFormatter.h"

#include "Net/Tools/Formatters/PeriodicProduct/PeriodicProductJSONFormatterBase.h"
#include "Net/Tools/Formatters/PeriodicProduct/PeriodicProductIdJSONFormatter.h"

#include "Net/Tools/Formatters/Statistics/BalanceJSONFormatter.h"
#include "Net/Tools/Formatters/Statistics/StatisticPerCategoryJSONFormatter.h"
#include "Net/Tools/Formatters/Statistics/StatisticPercentagePerCategoryJSONFormatter.h"
#include "Net/Tools/Formatters/Statistics/StatisticPerDayJSONFormatterBase.h"

#include "Net/Tools/Formatters/User/TokenJSONFormatter.h"

#include "Net/Tools/Formatters/ArrayJSONFormatterBase.h"

using IncomeCategoryJSONFormatter =
	IncomeCategoryJSONFormatterBase<IncomeCategory>;
using IncomeJSONFormatter =
	IncomeJSONFormatterBase<IncomeCategoryJSONFormatterBase, Income>;
using IncomesJSONFormatter =
	ArrayJSONFormatterBase<IncomeJSONFormatter, Income>;
using IncomeCategoriesJSONFormatter =
	ArrayJSONFormatterBase<IncomeCategoryJSONFormatter, IncomeCategory>;

using PeriodicIncomeJSONFormatter =
	PeriodicIncomeJSONFormatterBase<ProductCategoryJSONFormatterBase, PeriodicIncome>;
using PeriodicIncomesJSONFormatter =
	ArrayJSONFormatterBase<PeriodicIncomeJSONFormatter, PeriodicIncome>;

using ListStateJSONFormatter =
	ListStateJSONFormatterBase<ListState>;
using ListJSONFormatter =
	ListJSONFormatterBase<ListStateJSONFormatterBase, List>;
using ListsJSONFormatter =
	ArrayJSONFormatterBase<ListJSONFormatter, List>;
using ListStatesJSONFormatter =
	ArrayJSONFormatterBase<ListStateJSONFormatter, ListState>;

using ProductCategoryJSONFormatter =
	ProductCategoryJSONFormatterBase<ProductCategory>;
using ProductCategoriesJSONFormatter =
	ArrayJSONFormatterBase<ProductCategoryJSONFormatter, ProductCategory>;
using ProductJSONFormatter =
	ProductJSONFormatterBase<ProductCategoryJSONFormatterBase, Product>;
using ProductsJSONFormatter =
	ArrayJSONFormatterBase<ProductJSONFormatter, Product>;

using PeriodicProductJSONFormatter =
	PeriodicProductJSONFormatterBase<ProductCategoryJSONFormatterBase, PeriodicProduct>;
using PeriodicProductsJSONFormatter =
	ArrayJSONFormatterBase<PeriodicProductJSONFormatter, PeriodicProduct>;

using StatisticPerDayJSONFormatter =
	StatisticPerDayJSONFormatterBase<StatisticPerDay>;
using StatisticsPerDayJSONFormatter =
	ArrayJSONFormatterBase<StatisticPerDayJSONFormatter, StatisticPerDay>;
using StatisticsPerCategoryJSONFormatter =
	ArrayJSONFormatterBase<StatisticPerCategoryJSONFormatter, StatisticPerCategory>;
using StatisticsPercentagePerCategoryJSONFormatter =
	ArrayJSONFormatterBase<StatisticPercentagePerCategoryJSONFormatter, StatisticPercentagePerCategory>;
