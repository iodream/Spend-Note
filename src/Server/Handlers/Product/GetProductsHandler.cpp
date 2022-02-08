#include <QJsonArray>

#include "GetProductsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"

GetProductsHandler::GetProductsHandler()
{
}

Product GetProductsHandler::ToNetProduct(const db::Product& db_product, const db::ProductCategory& category)
{
	SCOPED_LOGGER;
	Product product;
	product.id = db_product.id;
	product.list_id = db_product.list_id;
	product.name = db_product.name;
	product.category.id = category.id;
	product.category.name = category.name;
	product.price = db_product.price;
	product.amount = db_product.amount;
	product.priority = db_product.product_priority;
	product.is_bought = db_product.is_bought;
	product.add_date = db_product.add_date;
	product.purchase_date = (db_product.purchase_date.has_value())? db_product.purchase_date.value() : EMPTY_STD_STRING;
	product.buy_until_date = (db_product.buy_until_date.has_value())? db_product.buy_until_date.value() : EMPTY_STD_STRING;

	return product;

}

Net::Response GetProductsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));
	auto db_products = m_facade->GetProductsForList(list_id);

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
