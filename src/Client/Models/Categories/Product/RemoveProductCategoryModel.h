#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/Product/ProductCategoryId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemoveProductCategoryModel
{
public:
	RemoveProductCategoryModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const ProductCategoryId& product_category_id);
private:
	std::string m_hostname{};

};
