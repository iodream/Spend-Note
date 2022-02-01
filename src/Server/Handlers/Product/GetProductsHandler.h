#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class GetProductsHandler : public AuthorizedHandler
{
	class JSONFormatter
	{
	public:
		using ProductItem = std::pair<const Product&, std::string>;

		using Products = std::vector<ProductItem>;

		QJsonDocument Format(const Products& dto);
	};

	class JSONParser
	{
	public:
		struct Product {
			IdType list_id;
		};
		Product Parse(const QJsonDocument& payload);
	};

public:
	GetProductsHandler(IDbFacade::Ptr facade);
	virtual ~GetProductsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
