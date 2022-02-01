#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "DTO/Product.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class AddProductModel
{
public:
	AddProductModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(/*const Product& product*/);
	// ProductId ParseResponse(const Net::Response response);
private:
	const std::string& m_hostname;
};
