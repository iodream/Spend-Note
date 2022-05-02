#pragma once

#include "../libdal/Types.h"

#include "../AuthorizedHandler.h"
#include <QJsonObject>
#include <QDateTime>
#include <QString>

#include "../Common.h"
#include "Server/Error.h"
#include "Server/Utils.h"
#include "../libdal/Facade/DbFacade.h"
#include "Net/Parsing.h"
#include "Logger/ScopedLogger.h"

class ChangeEmailHandler : public AuthorizedHandler
{
public:
    ChangeEmailHandler();
    virtual ~ChangeEmailHandler() override {}

	virtual Net::Response AuthHandle(const Net::Request& request) override;
private:

    class JSONParser
    {
    public:
        struct DTO
        {
            std::string code;
            std::string email;
        };
        DTO Parse(const QJsonDocument& json);
    } m_parser{};

};
