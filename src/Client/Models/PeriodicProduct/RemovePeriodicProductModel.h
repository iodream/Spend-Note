#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "Net/Entities/PeriodicProduct/PeriodicProductId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemovePeriodicProductModel
{
public:
	RemovePeriodicProductModel(const std::string& hostname) : m_hostname{hostname} {}

	Net::Request FormRequest(const PeriodicProductId& product_id);
private:
	std::string m_hostname{};

};
