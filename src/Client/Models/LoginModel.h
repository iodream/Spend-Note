#pragma once

#include <QJsonDocument>
#include <QJsonObject>

#include "DTO/Login.h"

class LoginModel
{
public:
    LoginModel();

    class JSONFormatter
    {
    public:
        QJsonDocument Form(LoginInDTO loginInDTO);
    };

    class JSONParser
    {
    public:
        LoginOutDTO Parse(QJsonDocument json);
    };

    void Request(LoginInDTO loginInDto);
};

