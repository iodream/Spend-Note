#pragma once

#include <string>
#include <memory>
#include <utility>

#include "../AuthorizedHandler.h"
#include "../libdal/DTOs/Product.h"

class RemoveIncomeHandler : public AuthorizedHandler
{
    class JSONParser
    {
    public:
        struct DTO {
            IdType id;
        };

        DTO Parse(const QJsonDocument& payload);
    };
public:
    RemoveIncomeHandler(IDbFacade::Ptr facade);
    virtual ~RemoveIncomeHandler() override {}

    Net::Response AuthHandle(const Net::Request& request) override;

private:
    JSONParser m_parser{};
};
