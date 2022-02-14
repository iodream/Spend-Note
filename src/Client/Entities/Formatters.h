#pragma once

#include "Entities.h"

#include "Net/Tools/Formatters/Income/IncomeCategoryJSONFormatterBase.h"
#include "Net/Tools/Formatters/Income/IncomeJSONFormatterBase.h"
#include "Net/Tools/Formatters/Income/IncomeIdJSONFormatter.h"

#include "Net/Tools/Formatters/List/ListJSONFormatterBase.h"
#include "Net/Tools/Formatters/List/ListStateJSONFormatterBase.h"
#include "Net/Tools/Formatters/List/ListIdJSONFormatter.h"

#include "Net/Tools/Formatters/Product/ProductCategoryJSONFormatterBase.h"
#include "Net/Tools/Formatters/Product/ProductJSONFormatterBase.h"
#include "Net/Tools/Formatters/Product/ProductIdJSONFormatter.h"

#include "Net/Tools/Formatters/Statistics/BalanceJSONFormatter.h"

#include "Net/Tools/Formatters/ArrayJSONFormatterBase.h"

using IncomeCategoryJSONFormatter =
	IncomeCategoryJSONFormatterBase<IncomeCategory>;
using IncomeJSONFormatter =
	IncomeJSONFormatterBase<IncomeCategoryJSONFormatterBase, Income>;
using IncomesJSONFormatter =
	ArrayJSONFormatterBase<IncomeJSONFormatter, Income>;

using ListStateJSONFormatter =
	ListStateJSONFormatterBase<ListState>;
using ListJSONFormatter =
	ListJSONFormatterBase<ListStateJSONFormatterBase, List>;
using ListsJSONFormatter =
	ArrayJSONFormatterBase<ListJSONFormatter, List>;

using ProductCategoryJSONFormatter =
	ProductCategoryJSONFormatterBase<ProductCategory>;
using ProductJSONFormatter =
	ProductJSONFormatterBase<ProductCategoryJSONFormatterBase, Product>;
using ProductsJSONFormatter =
	ArrayJSONFormatterBase<ProductJSONFormatter, Product>;
