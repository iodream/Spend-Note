#pragma once

#include <QMessageBox>

#include "Models/LoginModel.h"
#include "View/MainWindow.h"
#include "View/Constants.h"

class Controller : public QObject
{
    Q_OBJECT
public:
	Controller();
	void Start();

private:
	// HTTPClient httpClient;
	MainWindow main_window;

public slots:
    void OnLogin(LoginInDTO loginInDTO);
};
