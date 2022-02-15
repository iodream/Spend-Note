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

	Poco::Util::JSONConfiguration GetCfg()
	{
		const std::string config_filename =
			std::string(std::filesystem::current_path())
			+ std::string("/Config.json");

		return Poco::Util::JSONConfiguration(config_filename);

	}

	int main(const std::vector<std::string>&)
	{
		auto json_cfg = GetCfg();

		Logger::Init(json_cfg.getString("server_logger_name"), json_cfg.getString("server_scoped_logger_name"));
		ScopedLogger::Init(json_cfg.getString("server_scoped_logger_name"));

		SCOPED_LOGGER;

		Poco::UInt16 port = json_cfg.getUInt("port", 8080);

		auto* params = new Poco::Net::HTTPServerParams();
		params->setSoftwareVersion(
			std::string{"Spend&NoteServer/"}.
			append(std::string{SpendNoteServer_VERSION_MAJOR}).
			append(std::string{"."}).
			append(std::string{SpendNoteServer_VERSION_MINOR}));

		Poco::Net::HTTPServer srv(new HandlerFactory(), port);
		srv.start();
		qInfo() << "HTTP Server started on port " << port;
		waitForTerminationRequest();
		qInfo() << "Stopping HTTP Server...";
		srv.stop();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(HTTPServer)
