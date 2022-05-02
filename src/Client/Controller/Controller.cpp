#include "Controller.h"

#include <QJsonDocument>
#include <QFile>

#include "Models/LoginModel.h"
#include "Models/List/GetListsModel.h"

#include "Net/Constants.h"

Controller::Controller(QApplication* a)
	:m_app(a)
{
	m_trans = std::make_shared<QTranslator>();

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

		/*BUG: LANG_UI will be read a second time here while logging in and
		 MainPage::UISettings::LANG_UI = UILangs will be overwritten.
		 Hence if someone chooses a different language on the LoginPage, the translation will happen
		 but both the global var and the settings file will have the wrong value until the user chooses
		 the language in the settings menu */
		QString lang = json.value("LANG_UI").toString();

		if(lang == "English")
		{
			MainPage::UISettings::LANG_UI = UILangs::ENGLISH;
		}
		else if(lang == "Ukrainian")
		{
			MainPage::UISettings::LANG_UI = UILangs::UKRAINIAN;
		}
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

	m_login_page_controller->UpdateLoginPage();
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

	connect(
		m_main_page_controller.get(),
		&MainPageController::LangChanged,
		this,
		&Controller::OnLangChanged);
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
		m_login_page_controller->UpdateLoginPage();
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

void Controller::OnLangChanged()
{
	QString file;
	switch(MainPage::UISettings::LANG_UI)
	{
	case UILangs::ENGLISH:
		file = "en_US.qm";
		break;
	case UILangs::UKRAINIAN:
		file = "uk_UA.qm";
		break;
	default:
		file = "en_US.qm";
	}

	m_app->removeTranslator(m_trans.get());
	if(!m_trans->load(file))
	{
		qDebug() << "Couldnt load translation file\n";
	}

	m_app->installTranslator(m_trans.get());
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

	switch(MainPage::UISettings::LANG_UI)
	{
	case UILangs::ENGLISH:
		json["LANG_UI"] = "English";
		break;
	case UILangs::UKRAINIAN:
		json["LANG_UI"] = "Ukrainian";
		break;
	}

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
