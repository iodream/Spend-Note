#pragma once

#include "Poco/Util/JSONConfiguration.h"

class DbConnectionHelper
{
public:
	DbConnectionHelper() {};

	std::string FormConnectionString(const Poco::Util::JSONConfiguration& config) const;

private:
	const std::string USER = "user";
	const std::string HOST = "host";
	const std::string PASSWORD = "password";
	const std::string DBNAME = "dbname";
};
