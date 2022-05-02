#include "Controller.h"

#include <QJsonDocument>
#include <QFile>
#include <QApplication>

#include "Models/LoginModel.h"
#include "Models/List/GetListsModel.h"

#include "Net/Constants.h"

Controller::Controller(QApplication* a)
{
	m_app = a;
	m_trans = new QTranslator();
	m_trans->load("en_US.qm"); // default lang is eng
	m_app->installTranslator(m_trans);

	InitConfig();
	ReadSettings();

	InitLoginPageController();
	InitSignupPageController();
	InitMainPageController();

	connect(
		m_login_page_controller.get(),
		&LoginPageController::ReadSettings,
		this,
		&Controller::ReadSettings);

	connect(
		m_main_page_controller.get(),
		&MainPageController::SaveConfig,
		this,
		&Controller::OnSaveConfig);
	connect(
		&m_main_window,
		&MainWindow::SaveConfig,
		this,
		&Controller::OnSaveConfig);
}

void Controller::InitConfig()
{
	Poco::Util::JSONConfiguration m_json_configuration(config_filename);
	m_hostname = m_json_configuration.getString("hostname");
}

void Controller::ReadSettings()
{
	QFile file(settings_filename);
	if(!file.open(QIODevice::ReadOnly))
	{
		qDebug() << "couldn't open settings file";
		return;
	}
	QByteArray bytes = file.readAll();
	file.close();

	QJsonParseError jsonError;
	QJsonDocument document = QJsonDocument::fromJson(bytes, &jsonError);

	if(jsonError.error != QJsonParseError::NoError)
	{
		qDebug() << "parsing settings failed";
		return;
	}

	if(document.isObject())
	{
		QJsonObject json = document.object();
		MainPage::ColorSettings::LABEL_TEXT = json.value("COLOR_LABEL").toString();
		MainPage::ColorSettings::COLOR_TOP_BANNER = json.value("COLOR_TOP_BALANCE_BANNER").toString();
		MainPage::ColorSettings::WINDOW_BACKGROUND = json.value("COLOR_WINDOW_BACKGROUND").toString();
		MainPage::ColorSettings::PRODUCT_PRIO1 = json.value("COLOR_PRODUCT_PRIORITY1").toString();
		MainPage::ColorSettings::PRODUCT_PRIO2 = json.value("COLOR_PRODUCT_PRIORITY2").toString();
		MainPage::ColorSettings::PRODUCT_PRIO3 = json.value("COLOR_PRODUCT_PRIORITY3").toString();
		MainPage::ColorSettings::PRODUCT_PRIO4 = json.value("COLOR_PRODUCT_PRIORITY4").toString();
		MainPage::ColorSettings::PRODUCT_PRIO5 = json.value("COLOR_PRODUCT_PRIORITY5").toString();
		MainPage::ColorSettings::ERROR_BANNER = json.value("COLOR_ERROR_BANNER").toString();
		MainPage::ColorSettings::ERROR_BANNER = json.value("COLOR_ERROR_BANNER").toString();
		MainPage::ColorSettings::LIST_ACTIVE = json.value("COLOR_LIST_ACTIVE").toString();
		MainPage::ColorSettings::LIST_INACTIVE = json.value("COLOR_LIST_INACTIVE").toString();
		MainPage::ColorSettings::NAVBUTTONS = json.value("COLOR_NAVBUTTONS").toString();
		MainPage::ColorSettings::RECOMMENDATION = json.value("COLOR_RECOMMENDATION").toString();
	}
}

void Controller::InitLoginPageController()
{
	m_login_page_controller =
		std::make_unique<LoginPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_main_window.get_login_page());

	connect(
		m_login_page_controller.get(),
		&LoginPageController::ChangePage,
		this,
		&Controller::OnChangePage);
	connect(
		m_login_page_controller.get(),
		&LoginPageController::LangChanged,
		this,
		&Controller::OnLangChanged);
}

void Controller::InitSignupPageController()
{
	m_signup_page_controller =
		std::make_unique<SignupPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_main_window.get_signup_page());

	connect(
		m_signup_page_controller.get(),
		&SignupPageController::ChangePage,
		this,
		&Controller::OnChangePage);
}

void Controller::InitMainPageController()
{
	m_main_page_controller =
		std::make_unique<MainPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_main_window.get_main_page());

	connect(
		m_main_page_controller.get(),
		&MainPageController::ChangePage,
		this,
		&Controller::OnChangePage);

	connect(
		m_main_page_controller.get(),
		&MainPageController::ColorSchemeChanged,
		this,
		&Controller::OnColorSchemeChanged);
}

bool Controller::AskUser(const QString& title, const QString& text)
{
	return QMessageBox::Yes == QMessageBox::question(nullptr, tr("Retry?"),
											tr("No connection to server. Retry?"));
}

void Controller::Start(UIPages at_page)
{
	m_main_window.show();
	MainWindow::active_page = at_page;
	m_main_window.SetCurrentPage(at_page);
}

void Controller::SetPage(UIPages page)
{
	switch (page) {
	case UIPages::MAIN:
		m_main_page_controller->ChangeSubPage(MainSubPages::LISTS);

		break;
	case UIPages::LOGIN:
		break;
	case UIPages::SIGNUP:
		break;
	}
	MainWindow::active_page = page;

	m_main_window.SetCurrentPage(page);
}

void Controller::OnChangePage(UIPages page)
{
	SetPage(page);
}

void Controller::OnLangChanged(const UILangs& lang)
{
	switch(lang)
	{
	case UILangs::ENGLISH:
		m_app->removeTranslator(m_trans);
		m_trans->load("en_US.qm");
		m_app->installTranslator(m_trans);
		break;
	case UILangs::UKRAINIAN:
		m_app->removeTranslator(m_trans);
		m_trans->load("uk_UA.qm");
		m_app->installTranslator(m_trans);
		break;
	}
}

void Controller::OnSaveConfig()
{
	QJsonObject json;
	json["COLOR_TOP_BALANCE_BANNER"] = MainPage::ColorSettings::COLOR_TOP_BANNER;
	json["COLOR_WINDOW_BACKGROUND"] = MainPage::ColorSettings::WINDOW_BACKGROUND;
	json["COLOR_PRODUCT_PRIORITY1"] = MainPage::ColorSettings::PRODUCT_PRIO1;
	json["COLOR_PRODUCT_PRIORITY2"] = MainPage::ColorSettings::PRODUCT_PRIO2;
	json["COLOR_PRODUCT_PRIORITY3"] = MainPage::ColorSettings::PRODUCT_PRIO3;
	json["COLOR_PRODUCT_PRIORITY4"] = MainPage::ColorSettings::PRODUCT_PRIO4;
	json["COLOR_PRODUCT_PRIORITY5"] = MainPage::ColorSettings::PRODUCT_PRIO5;
	json["COLOR_ERROR_BANNER"] = MainPage::ColorSettings::ERROR_BANNER;
	json["COLOR_LIST_ACTIVE"] = MainPage::ColorSettings::LIST_ACTIVE;
	json["COLOR_LIST_INACTIVE"] = MainPage::ColorSettings::LIST_INACTIVE;
	json["COLOR_LABEL"] = MainPage::ColorSettings::LABEL_TEXT;
	json["COLOR_NAVBUTTONS"] = MainPage::ColorSettings::NAVBUTTONS;
	json["COLOR_RECOMMENDATION"] = MainPage::ColorSettings::RECOMMENDATION;

	QFile file(settings_filename);
	QByteArray bytes = QJsonDocument(json).toJson( QJsonDocument::Indented );
	if (!file.open(QIODevice::WriteOnly))
	{
		qWarning("Couldn't open settings save file");
		return;
	}
		QTextStream iStream( &file );
		iStream << bytes;
		file.close();
}

void Controller::OnColorSchemeChanged()
{
	m_main_window.UpdateColors();
}
