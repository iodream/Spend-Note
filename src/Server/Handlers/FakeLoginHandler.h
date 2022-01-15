#pragma once

#include <string>

#include "ICommandHandler.h"

class FakeLoginHandler : public ICommandHandler
{
    struct InDTO
    {
    };

    struct OutDTO
    {
        std::string token;
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
    FakeLoginHandler() {}
    virtual ~FakeLoginHandler() override {}

    QJsonDocument Handle(const QJsonDocument& json_doc) override;

    Parser m_parser{};
    Formatter m_formatter{};
};
