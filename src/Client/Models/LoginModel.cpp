#include "LoginModel.h"

LoginModel::LoginModel()
{

}

void LoginModel::Request(LoginInDTO loginInDto)
{

}


QJsonDocument LoginModel::JSONFormatter::Form(LoginInDTO loginInDTO)
{
    QJsonObject json;
    json.insert("login", QString::fromStdString(loginInDTO.login));
    json.insert("password", QString::fromStdString(loginInDTO.password));
    return QJsonDocument(json);
}

LoginOutDTO LoginModel::JSONParser::Parse(QJsonDocument json)
{

}
