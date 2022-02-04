#pragma once

#include <string>

#include "Net/Entities/Income/IncomeBase.h"
#include "Net/Entities/Income/IncomeId.h"
#include "Net/Entities/Income/IncomeCategoryBase.h"

#include "Net/Entities/List/ListBase.h"
#include "Net/Entities/List/ListId.h"
#include "Net/Entities/List/ListStateBase.h"

#include "Net/Entities/Product/ProductBase.h"
#include "Net/Entities/Product/ProductId.h"
#include "Net/Entities/Product/ProductCategoryBase.h"

using String = std::string;

using Income = IncomeBase<IncomeCategoryBase, String>;
using IncomeCategory = IncomeCategoryBase<String>;

using List = ListBase<ListStateBase, String>;
using ListState = ListStateBase<String>;

using Product = ProductBase<ProductCategoryBase, String>;
using ProductCategory = ProductCategoryBase<String>;
