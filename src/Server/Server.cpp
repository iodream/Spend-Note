#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Net/NetException.h"

#include "Net/Constants.h"
#include "HandlerFactory.h"
#include "ConfigManager.h"
#include "SpendNoteServer_Config.h"
#include "Logger/ScopedLogger.h"
#include "Logger/Logger.h"

class HTTPServer: public Poco::Util::ServerApplication
{
	void initialize(Application& self)
	{
		SCOPED_LOGGER;
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	int main(const std::vector<std::string>&)
	{
		auto json_config = ConfigManager::GetConfig();

		if(!ConfigManager::isConfigFull(json_config))
		{
			qCritical() << "Config invalid!";
			return Application::EXIT_CONFIG;
		}

		Logger::Init(json_config.getString(Config::SERVER_LOGGER_NAME), json_config.getString(Config::SERVER_SCOPED_LOGGER_NAME));
		ScopedLogger::Init(json_config.getString(Config::SERVER_SCOPED_LOGGER_NAME));

		SCOPED_LOGGER;

		Poco::UInt16 port = json_config.getUInt(Config::PORT);

		auto* params = new Poco::Net::HTTPServerParams();
		params->setSoftwareVersion(
			std::string{"Spend&NoteServer/"}.
			append(std::string{SpendNoteServer_VERSION_MAJOR}).
			append(std::string{"."}).
			append(std::string{SpendNoteServer_VERSION_MINOR}));

		Poco::Net::HTTPServer srv(new HandlerFactory(json_config), port);
		srv.start();
		qInfo() << "HTTP Server started on port " << port;
		waitForTerminationRequest();
		qInfo() << "Stopping HTTP Server...";
		srv.stop();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(HTTPServer)
