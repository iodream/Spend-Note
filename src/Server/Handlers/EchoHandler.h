#pragma once

#include <string>

#include "ICommandHandler.h"

class EchoHandler : public ICommandHandler
{
    struct InDTO
    {
        std::string msg;
    };

    struct OutDTO
    {
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
    EchoHandler() {}
    virtual ~EchoHandler() override {}

    QJsonDocument Handle(const QJsonDocument& json_doc) override;

    Parser m_parser{};
    Formatter m_formatter{};
};
