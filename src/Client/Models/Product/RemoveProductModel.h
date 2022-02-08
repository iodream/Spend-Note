#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/Product/ProductId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemoveProductModel
{
public:
	RemoveProductModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const ProductId& product_id);
private:
	std::string m_hostname{};

};
