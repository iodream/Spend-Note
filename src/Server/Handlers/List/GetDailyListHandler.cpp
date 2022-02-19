#include <QJsonArray>

#include "GetDailyListHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../Product/Utils.h"
#include "../libdal/Exceptions/NonexistentResource.h"

GetDailyListHandler::GetDailyListHandler()
{
}

Net::Response GetDailyListHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto user_id = std::get<long long>(m_params.Get(Params::USER_ID));
	std::vector<db::Product> db_products;
	db_products = m_facade->GetDailyList(user_id);

	std::vector<Product> products;
	for (const db::Product& db_product : db_products) {
		auto category = m_facade->GetProductCategoryById(db_product.category_id);
		if (!category.has_value())
		{
			throw InternalError(std::string("No product category with id:") + std::to_string(db_product.category_id));
		}
		auto product = ToNetProduct(db_product, category.value());
		products.push_back(product);
	}

	return FormJSONResponse(m_formatter.Format(products));
}
