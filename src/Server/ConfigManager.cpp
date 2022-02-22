#include "ConfigManager.h"

bool ConfigManager::isConfigFull(const Poco::Util::JSONConfiguration& config)
{
	return
		config.has(Config::USER) &&
		config.has(Config::HOST) &&
		config.has(Config::PASSWORD) &&
		config.has(Config::DBNAME) &&
		config.has(Config::PORT) &&
		config.has(Config::SERVER_LOGGER_NAME) &&
		config.has(Config::SERVER_SCOPED_LOGGER_NAME) &&
		config.has(Config::CONFIG_DIRECTORY);
}

Poco::Util::JSONConfiguration ConfigManager::GetConfig()
{
	return Poco::Util::JSONConfiguration("Config.json");
}