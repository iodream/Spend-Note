#pragma once

#include <QMessageBox>

#include "HTTPClient.h"
#include "NavHistory.h"

#include "View/MainWindow.h"
#include "View/MainPage/MainPage.h"
#include "Models/SignupModel.h"
#include "View/Constants.h"
#include "Models/LoginModel.h"

class Controller : public QObject
{
	Q_OBJECT
public:
	using SignupInDTO = SignupModel::SignupInDTO;

	Controller();
	void Start(UIPages at_page=UIPages::LOGIN);

	void StartTest();

private:
	std::string m_hostname{"http://localhost:8080"};

	HTTPClient m_http_client;

	NavHistory m_history;
	MainWindow m_main_window;

	IdType m_user_id{1};

	bool UpdateMainListsSubPage();
	void SetMainSubPage(MainSubPages page);

	void ConnectLoginPage();
	void ConnectMainPage();
	void ConnectSignupPage();

public slots:

	void OnGotoLoginPage();

	void OnLogin(LoginModel::JSONFormatter::Credentials credentials);
	void OnLogout();
	void OnChangeMainSubPage(MainSubPages page);
	void OnGoToSignupPage();
	void OnSignup(const SignupInDTO& in_dto);
	void OnGoBack();
//	void OnLoadLists();
//	void OnLoadProducts();
//	void OnLoadProducts();
};
