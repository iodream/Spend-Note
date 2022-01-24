#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class RemoveListHandler : public AuthorizedHandler
{
    class JSONParser
    {
    public:
		struct ListDTO {
            IdType id;
        };

		ListDTO Parse(const QJsonDocument& payload);
    };
public:
    RemoveListHandler(IDbFacade::Ptr facade);
    virtual ~RemoveListHandler() override {}

    Net::Response AuthHandle(const Net::Request& request) override;

private:
    JSONParser m_parser{};
};
