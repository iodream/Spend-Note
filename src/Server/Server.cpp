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
		loadConfiguration();
		ServerApplication::initialize(self);
	}

	int main(const std::vector<std::string>&)
	{
		SCOPED_LOGGER;
		Logger::Init("Server.log");
		Poco::UInt16 port = static_cast<Poco::UInt16>(config().getUInt("port", 8080));

		auto* params = new Poco::Net::HTTPServerParams();
		params->setSoftwareVersion(
			std::string{"Spend&NoteServer/"}.
			append(std::string{SpendNoteServer_VERSION_MAJOR}).
			append(std::string{"."}).
			append(std::string{SpendNoteServer_VERSION_MINOR}));

		Poco::Net::HTTPServer srv(new HandlerFactory, port);
		srv.start();
		qDebug() << "HTTP Server started on port " << port << "\n";
		waitForTerminationRequest();
		qDebug() << "Stopping HTTP Server..." << "\n";
		srv.stop();

		return Application::EXIT_OK;
	}
};

POCO_SERVER_MAIN(HTTPServer)
