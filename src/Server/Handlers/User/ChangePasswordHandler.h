#pragma once

#include <QDateTime>
#include <Poco/JWT/Token.h>
#include <Poco/JWT/Signer.h>

#include "../libdal/Types.h"
#include "../AuthorizedHandler.h"
#include "../Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Logger/ScopedLogger.h"
#include "../Entities/Entities.h"
#include "../Entities/Parsers.h"
#include "../Entities/Formatters.h"

class ChangePasswordHandler : public AuthorizedHandler
{
public:
	ChangePasswordHandler() {}
	virtual ~ChangePasswordHandler() override {}
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	PasswordUpdateJSONParser m_parser{};
	TokenJSONFormatter m_formatter{};
};
