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

class ChangePasswordHandler : public AuthorizedHandler
{
public:
	ChangePasswordHandler() {} ;
	virtual ~ChangePasswordHandler() override {};
	virtual Net::Response AuthHandle(const Net::Request& request) override;

private:
	class JSONParser{
	public:
		struct DTO
		{
			std::string code;
			std::string password;
		};
		DTO Parse(const QJsonObject& json);
	} m_parser{};
};
