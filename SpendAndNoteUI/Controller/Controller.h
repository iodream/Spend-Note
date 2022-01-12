#pragma once
#include "Model/LoginModel.h"
#include "View/MainWindow.h"
#include "./Constants.h"

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
