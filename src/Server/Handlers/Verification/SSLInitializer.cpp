#include "Poco/Net/SSLManager.h"

#include "SSLInitializer.h"

using Poco::Net::SSLManager;

SSLInitializer::SSLInitializer()
{
	Poco::Net::initializeSSL();
}

SSLInitializer::~SSLInitializer()
{
	Poco::Net::uninitializeSSL();
}
