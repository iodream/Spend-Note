#pragma once

#include <QMessageBox>

#include "View/MainWindow.h"
#include "View/MainPage/MainPage.h"
#include "Models/SignupModel.h"

#include "View/Constants.h"
#include "HTTPClient.h"

class Controller : public QObject
{
	Q_OBJECT
public:
	using SignupInDTO = SignupModel::SignupInDTO;

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
	void ConnectSignupPage();

public slots:
	void OnLogin(LoginInDTO loginInDTO);
	void OnGotoLoginPage();
	void OnLogout();
	void OnChangeMainSubPage(MainSubPages page);
	void OnGotoSignupPage();
	void OnSignup(const SignupInDTO& in_dto);
//	void OnMoveBack();
//	void OnLoadLists();
//	void OnLoadProducts();
//	void OnLoadProducts();
};
