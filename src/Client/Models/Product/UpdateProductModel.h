#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Entities/Formatters.h"
#include "Entities/Parsers.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class UpdateProductModel
{
public:
	UpdateProductModel(std::string hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const Product& product);
private:
	const std::string& m_hostname{};

	ProductJSONFormatter m_formatter{};
};


