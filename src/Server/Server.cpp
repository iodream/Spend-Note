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

	bool isConfigOK(const Poco::Util::JSONConfiguration& config)
	{
		if(!config.has("user") || !config.has("host")
			|| !config.has("password") || !config.has("dbname")
			|| !config.has("port") || !config.has("server_logger_name")
			|| !config.has("server_scoped_logger_name")
			|| !config.has("config_directory")) return false;

		return true;
	}

	int main(const std::vector<std::string>&)
	{
		auto json_config = HandlerFactory::GetConfig();

		if(!isConfigOK(json_config))
		{
			qCritical() << "Config invalid!";
			return Application::EXIT_CONFIG;
		}

		Logger::Init(json_config.getString("server_logger_name"), json_config.getString("server_scoped_logger_name"));
		ScopedLogger::Init(json_config.getString("server_scoped_logger_name"));

		SCOPED_LOGGER;

		Poco::UInt16 port = json_config.getUInt("port");

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
