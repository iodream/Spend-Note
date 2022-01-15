#pragma once

#include <QJsonDocument>

class ICommandHandler
{
public:
    ICommandHandler() {}
    virtual ~ICommandHandler() {}

    virtual QJsonDocument Handle(const QJsonDocument& json_doc) = 0;
};
