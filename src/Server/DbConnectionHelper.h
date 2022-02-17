#pragma once

#include "Poco/Util/JSONConfiguration.h"

#include "ConfigManager.h"

class DbConnectionHelper
{
public:
	DbConnectionHelper() {};

	std::string FormConnectionString(const Poco::Util::JSONConfiguration& config) const;
};
