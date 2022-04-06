#pragma once

#include "Net/Entities/Income/IncomeCategoryId.h"
#include "Net/Constants.h"
#include "Net/Message.h"

class RemoveIncomeCategoryModel
{
public:
	RemoveIncomeCategoryModel(const std::string& hostname) : m_hostname{hostname} {};

	Net::Request FormRequest(const IncomeCategoryId& category_id);
private:
	std::string m_hostname{};
};
