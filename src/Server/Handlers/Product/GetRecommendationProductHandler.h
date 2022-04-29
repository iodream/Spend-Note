#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"

#include "../Entities/Entities.h"
#include "../Entities/Formatters.h"

#include "../libdal/DTOs/Product.h"

class GetRecommendationProductHandler : public AuthorizedHandler
{
public:
	GetRecommendationProductHandler();
	virtual ~GetRecommendationProductHandler() override {}

	Net::Response AuthHandle(const Net::Request& request) override;
private:
	ProductJSONFormatter m_formatter;
};
