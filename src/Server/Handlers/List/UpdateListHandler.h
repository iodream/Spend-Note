#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/List.h"

class UpdateListHandler : public AuthorizedHandler
{
    UpdateListHandler(IDbFacade::Ptr facade);
    virtual ~UpdateListHandler(){};

    Net::Response AuthHandle(const Net::Request& request) override;

public:
    class JSONParser
    {
    public:
        List Parser(const QJsonDocument& payload);
    };

private:
    JSONParser m_parser;
};
