#pragma once

#include <memory>

#include <QMessageBox>

#include "Poco/Util/JSONConfiguration.h"

#include "HTTPClient.h"

#include "LoginPageController.h"
#include "SignupPageController.h"
#include "MainPage/MainPageController.h"

#include "View/MainWindow.h"
#include "View/Constants.h"

class Controller : public QObject
{
	Q_OBJECT
public:
	using SignupInDTO = SignupModel::SignupInDTO;

	Controller();
	void Start(UIPages at_page=UIPages::LOGIN);

private:
	void SetPage(UIPages page);

	void InitLoginPageController();
	void InitSignupPageController();
	void InitMainPageController();

private:
	std::string m_hostname;
	HTTPClient m_http_client;
	IdType m_user_id{1};
	MainWindow m_main_window{};

private:
	std::unique_ptr<LoginPageController>  m_login_page_controller;
	std::unique_ptr<SignupPageController> m_signup_page_controller;
	std::unique_ptr<MainPageController>   m_main_page_controller;

public slots:
	void OnMessage(const QString& window_name, const QString& message);
	void OnChangePage(UIPages page);
};
