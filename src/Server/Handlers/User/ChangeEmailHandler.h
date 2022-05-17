#pragma once

#include <QDateTime>
#include "../libdal/Types.h"
#include "../AuthorizedHandler.h"
#include "../Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Logger/ScopedLogger.h"
#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"

class ChangeEmailHandler : public AuthorizedHandler
{
public:
	ChangeEmailHandler();
	virtual ~ChangeEmailHandler() override {}

	virtual Net::Response AuthHandle(const Net::Request& request) override;
private:
	EmailUpdateJSONParser m_parser{};
};
