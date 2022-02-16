#include <QJsonArray>

#include "GetProductCategoriesHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "Utils.h"

GetProductCategoriesHandler::GetProductCategoriesHandler()
{
}

Net::Response GetProductCategoriesHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto db_product_categories = m_facade->GetAllProductCategories();
	std::vector<ProductCategory> product_categories;

	for (const db::ProductCategory& db_product_category : db_product_categories) {
		auto product_category = ToNetProductCategory(db_product_category);
		product_categories.push_back(product_category);
	}

	return FormJSONResponse(m_formatter.Format(product_categories));
}
