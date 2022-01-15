#pragma once

#include <string>

#include "ICommandHandler.h"

class FakeGetListsHandler : public ICommandHandler
{
    struct InDTO
    {
        std::string token;
        std::string user;
    };

    struct OutDTO
    {
        std::string user;
        std::string msg;
    };

    class Parser
    {
    public:
        InDTO Parse(const QJsonDocument& json_doc);
    };

    class Formatter
    {
    public:
        QJsonDocument Format(const OutDTO& dto);
    };

public:
    FakeGetListsHandler() {}
    virtual ~FakeGetListsHandler() override {}

    QJsonDocument Handle(const QJsonDocument& json_doc) override;

    Parser m_parser{};
    Formatter m_formatter{};
};
