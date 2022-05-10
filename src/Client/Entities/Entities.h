#pragma once

#include <QString>

#include "Net/Entities/Income/IncomeBase.h"
#include "Net/Entities/Income/IncomeId.h"
#include "Net/Entities/Income/IncomeCategoryBase.h"
#include "Net/Entities/Income/IncomeCategoryId.h"

#include "Net/Entities/PeriodicIncome/PeriodicIncomeBase.h"
#include "Net/Entities/PeriodicIncome/PeriodicIncomeId.h"

#include "Net/Entities/List/ListBase.h"
#include "Net/Entities/List/ListId.h"
#include "Net/Entities/List/ListStateBase.h"

#include "Net/Entities/Product/ProductBase.h"
#include "Net/Entities/Product/ProductId.h"
#include "Net/Entities/Product/ProductCategoryBase.h"
#include "Net/Entities/Product/ProductCategoryId.h"

#include "Net/Entities/Statistics/Balance.h"
#include "Net/Entities/Statistics/StatisticPerCategory.h"
#include "Net/Entities/Statistics/StatisticPercentagePerCategory.h"
#include "Net/Entities/Statistics/StatisticPerDayBase.h"

#include "Net/Entities/PeriodicProduct/PeriodicProductBase.h"
#include "Net/Entities/PeriodicProduct/PeriodicProductId.h"

using String = QString;

using Income = IncomeBase<IncomeCategoryBase, String>;
using IncomeCategory = IncomeCategoryBase<String>;
using PeriodicIncome = PeriodicIncomeBase<IncomeCategoryBase, String>;

using List = ListBase<ListStateBase, String>;
using ListState = ListStateBase<String>;

using Product = ProductBase<ProductCategoryBase, String>;
using ProductCategory = ProductCategoryBase<String>;

using PeriodicProduct = PeriodicProductBase<ProductCategoryBase, String>;

using StatisticPerDay = StatisticPerDayBase<String>;
