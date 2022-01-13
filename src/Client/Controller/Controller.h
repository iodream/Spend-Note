#pragma once
#include "Models/LoginModel.h"
#include "Views/MainWindow.h"
#include "Views/Constants.h"

class Controller : public QObject
{
    Q_OBJECT
public:

   // HTTPClient httpClient;

signals:
    void OnSuccessLogin(UIPages);
    void OnUnsuccessLogin(std::string reason);

public slots:
    void OnLogin(LoginInDTO loginInDTO);
};
