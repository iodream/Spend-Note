#include "Controller.h"

#include "Models/LoginModel.h"
#include "Models/List/GetListsModel.h"

#include "Net/Constants.h"

Controller::Controller()
{
	InitConfig();
	InitLoginPageController();
	InitSignupPageController();
	InitMainPageController();
}

void Controller::InitConfig()
{
	Poco::Util::JSONConfiguration m_json_configuration(config_filename);

	m_hostname = m_json_configuration.getString("hostname");
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
		&LoginPageController::SetEmail,
		this,
		&Controller::OnSetEmail);
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
		this,
		&Controller::SetEmail,
		m_main_page_controller.get(),
		&MainPageController::OnSetEmail);
}

bool Controller::AskUser(const QString& title, const QString& text)
{
	return QMessageBox::Yes == QMessageBox::question(nullptr, QString("Retry?"),
													 QString("No connection to server. Retry?"));
}

void Controller::Start(UIPages at_page)
{
	m_main_window.show();
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

	m_main_window.SetCurrentPage(page);
}

void Controller::OnChangePage(UIPages page)
{
	SetPage(page);
}

void Controller::OnSetEmail(const std::string& email)
{
	emit SetEmail(email);
}
