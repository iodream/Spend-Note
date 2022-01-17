#pragma once

#include <QMessageBox>

#include "Models/LoginModel.h"
#include "View/MainWindow.h"
#include "View/Constants.h"
#include "HTTPClient.h"

class Controller : public QObject
{
    Q_OBJECT
public:
	Controller();
	void Start(UIPages at_page=UIPages::LOGIN);

	void StartTest();

private:
	HTTPClient m_http_client;
	MainWindow m_main_window;

public slots:
    void OnLogin(LoginInDTO loginInDTO);
};
