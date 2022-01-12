#pragma once

#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "DTO/Login.h"

class LoginModel
{
public:

    class JSONFormatter
    {
    public:
        QJsonDocument Format(LoginInDTO loginInDTO);
    };

    class JSONParser
    {
    public:
        // InnerDTO Parse(QJsonDocument json);
    };

    void RequestDTO(LoginInDTO loginInDTO);
};
