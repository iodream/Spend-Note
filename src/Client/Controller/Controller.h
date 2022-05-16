#pragma once

#include <memory>

#include <QMessageBox>
#include <QApplication>
#include <QTranslator>

#include "Poco/Util/JSONConfiguration.h"

#include "HTTPClient.h"

#include "LoginPageController.h"
#include "SignupPageController.h"
#include "MainPage/MainPageController.h"


#include "View/MainWindow.h"
#include "View/Constants.h"

namespace{
const std::string config_filename = "Config.json";
const QString settings_filename = "Settings.json";
}

class Controller : public QObject
{
	Q_OBJECT
public:
	using SignupInDTO = SignupModel::SignupInDTO;

	Controller(QApplication* a);
	void Start(UIPages at_page=UIPages::LOGIN);
	static bool AskUser(const QString& title, const QString& text);

private:
	void SetPage(UIPages page);

	void InitConfig();

	void InitLoginPageController();
	void InitSignupPageController();
	void InitMainPageController();
private:
	std::string m_hostname;
	HTTPClient m_http_client;
	IdType m_user_id{1};
	MainWindow m_main_window{};
	QApplication* m_application;
	std::shared_ptr<QTranslator> m_translator;

private:
	std::unique_ptr<LoginPageController>  m_login_page_controller;
	std::unique_ptr<SignupPageController> m_signup_page_controller;
	std::unique_ptr<MainPageController>   m_main_page_controller;

public slots:
	void OnChangePage(UIPages page);

signals:
	void SetEmail(const std::string& email);

private:
	void OnLanguageChanged();
	void OnSaveConfig();
	void OnColorSchemeChanged();
	void ReadSettings();
	void OnScaleMinimumSize();
};
