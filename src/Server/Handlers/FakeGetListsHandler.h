#pragma once

#include <string>

#include "AuthorizedHandler.h"

class FakeGetListsHandler : public AuthorizedHandler
{
public:
    class JSONParser
    {
    public:
        struct DTO
        {
            std::string user;
        };

        DTO Parse(const QJsonDocument& token_body);
    };

    class JSONFormatter
    {
    public:
        struct DTO
        {
            std::string user;
            std::string msg;
        };

        QJsonDocument Format(const DTO& dto);
    };

	FakeGetListsHandler(IDbFacade::Ptr facade) : AuthorizedHandler(std::move(facade)) {}
    virtual ~FakeGetListsHandler() override {}

    virtual Net::Response AuthHandle(const Net::Request& request) override;

    JSONParser m_parser{};
    JSONFormatter m_formatter{};
};
