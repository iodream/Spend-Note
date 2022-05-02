#include <QJsonArray>

#include "GetPeriodicProductsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"
#include "../libdal/Exceptions/NonexistentResource.h"
#include "Utils.h"

GetProductsHandler::GetProductsHandler()
{
}

Net::Response GetProductsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	auto list_id = std::get<long long>(m_params.Get(Params::LIST_ID));

	if (!m_facade->CanUserEditList(request.uid, list_id)){
		return FormErrorResponse(
			NetError::Status::HTTP_FORBIDDEN,
			"User with id \"" + std::to_string(request.uid) +
			"\" can't get products for list with id \"" + std::to_string(list_id) + "\"");;
	}

	std::vector<db::PeriodicProduct> db_products;
	try
	{
		db_products = m_facade->GetPeriodicProductsForList(list_id);
	}
	catch (const db::NonexistentResource& ex) {
		return FormErrorResponse(
			NetError::Status::HTTP_NOT_FOUND,
			"List with id = \"" + std::to_string(list_id) + "\" not found");
	}

	std::vector<PeriodicProduct> products;
	for (const db::Product& db_product : db_products) {
		auto category = m_facade->GetProductCategoryById(db_product.category_id);
		if (!category.has_value())
		{
			throw InternalError(std::string("No product category with id:") + std::to_string(db_product.category_id));
		}
		auto product = ToNetPeriodProduct(db_product, category.value());
		products.push_back(product);
	}

	return FormJSONResponse(m_formatter.Format(products));
}
