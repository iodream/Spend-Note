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
		using DTOItem = std::pair<const Product&, std::string>;

		using DTO = std::vector<DTOItem>;

		QJsonDocument Format(const DTO& dto);
	};

	class JSONParser
	{
	public:
		struct DTO {
			IdType list_id;
		};
		DTO Parse(const QJsonDocument& payload);
	};

public:
	GetProductsHandler(IDbFacade::Ptr facade);
	virtual ~GetProductsHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;

private:
	JSONFormatter m_formatter{};
	JSONParser m_parser{};
};
