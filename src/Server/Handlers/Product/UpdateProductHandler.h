#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class UpdateProductHandler : public AuthorizedHandler
{
public:
	UpdateProductHandler();
	virtual ~UpdateProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	db::Product ToDBProduct(const Product& product);
private:
	ProductJSONParser m_parser{};
};
