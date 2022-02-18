#pragma once

#include "Poco/Util/JSONConfiguration.h"

namespace Config{
const std::string USER = "user";
const std::string HOST = "host";
const std::string PASSWORD = "password";
const std::string DBNAME = "dbname";
const std::string PORT = "port";
const std::string SERVER_LOGGER_NAME = "server_logger_name";
const std::string SERVER_SCOPED_LOGGER_NAME = "server_scoped_logger_name";
const std::string CONFIG_DIRECTORY = "config_directory";
}

class ConfigManager
{
public:
	static bool isConfigFull(const Poco::Util::JSONConfiguration& config);
	static Poco::Util::JSONConfiguration GetConfig();
};
