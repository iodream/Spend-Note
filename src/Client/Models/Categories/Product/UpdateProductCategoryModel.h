#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdateProductCategoryModel
{
public:
	UpdateProductCategoryModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const ProductCategory& product_category);
private:
	const std::string& m_hostname{};

	ProductCategoryJSONFormatter m_formatter{};
};


