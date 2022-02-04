#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class AddProductHandler : public AuthorizedHandler
{
	class JSONParser
	{
	public:
		db::Product Parse(const QJsonDocument& payload);
	};

	class JSONFormatter
	{
	public:
		struct Product {
			db::IdType id;
		};

		QJsonDocument Format(const Product& dto);
	};
public:
	AddProductHandler();
	virtual ~AddProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
