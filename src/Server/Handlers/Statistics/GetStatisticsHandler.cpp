#include <QJsonArray>

#include "GetStatisticsHandler.h"
#include "Net/Parsing.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../Common.h"
#include "Logger/ScopedLogger.h"


GetStatisticsHandler::GetStatisticsHandler()
{
}

Net::Response GetStatisticsHandler::AuthHandle(const Net::Request& request)
{
	SCOPED_LOGGER;
	Q_UNUSED(request);

	return FormEmptyResponse();
}
