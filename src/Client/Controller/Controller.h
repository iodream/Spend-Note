#pragma once

#include <QMessageBox>

#include "View/MainWindow.h"
#include "View/MainPage/MainPage.h"
#include "View/Constants.h"

#include "Models/LoginModel.h"

#include "HTTPClient.h"

class Controller : public QObject
{
	Q_OBJECT
public:
	Controller();
	void Start(UIPages at_page=UIPages::LOGIN);

	void StartTest();

private:
	std::string m_hostname{"http://localhost:8080/"};

	HTTPClient m_http_client;
	MainWindow m_main_window;

	void UpdateMainListsSubPage();
	void SetMainSubPage(MainSubPages page);

	void ConnectLoginPage();
	void ConnectMainPage();

public slots:
	void OnLogin(LoginModel::JSONFormatter::LoginInDTO loginInDTO);
	void OnLogout();
	void OnChangeMainSubPage(MainSubPages page);
//	void OnMoveBack();
//	void OnLoadLists();
//	void OnLoadProducts();
//	void OnLoadProducts();
};
