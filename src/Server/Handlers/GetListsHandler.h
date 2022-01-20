#pragma once

#include <string>
#include <vector>

#include "AuthorizedHandler.h"

using IdType= long long int;

class GetListsHandler : public AuthorizedHandler
{
    class JSONFormatter
    {
    public:
        struct DTO
        {
            IdType id;
            IdType ownerId;
            IdType stateId;
            std::string name;
        };

        QJsonDocument Format(const std::vector<DTO>& dtoVector);
    };

    GetListsHandler() {}
    virtual ~GetListsHandler() override {}

    virtual Net::Response AuthHandle(const Net::Request& request) override;

    JSONFormatter m_formatter{};
};
