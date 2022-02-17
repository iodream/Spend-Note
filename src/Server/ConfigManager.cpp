#include "ConfigManager.h"

bool ConfigManager::isConfigFull(const Poco::Util::JSONConfiguration& config)
{
	return
		config.has(USER) &&
		config.has(HOST) &&
		config.has(PASSWORD) &&
		config.has(DBNAME) &&
		config.has(PORT) &&
		config.has(SERVER_LOGGER_NAME) &&
		config.has(SERVER_SCOPED_LOGGER_NAME) &&
		config.has(CONFIG_DIRECTORY);
}

Poco::Util::JSONConfiguration ConfigManager::GetConfig()
{
	return Poco::Util::JSONConfiguration("Config.json");
}
