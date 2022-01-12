#include "LoginModel.h"

QJsonDocument LoginModel::JSONFormatter::Format(LoginInDTO loginInDTO)
{
    QJsonObject json;
    json.insert("login", QString::fromStdString(loginInDTO.login));
    json.insert("password", QString::fromStdString(loginInDTO.password));
    return QJsonDocument(json);
}

void LoginModel::RequestDTO(LoginInDTO loginInDTO)
{

};
