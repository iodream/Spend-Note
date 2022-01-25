#include "Controller.h"

#include "Models/LoginModel.h"
#include "Models/List/GetListsModel.h"

#include "Net/Constants.h"

Controller::Controller()
{
	ConnectLoginPage();
	ConnectMainPage();
	ConnectSignupPage();
}

void Controller::ConnectLoginPage()
{
	auto& page = m_main_window.get_login_page();

	QObject::connect(
		&page,
		&LoginPage::Login,
		this,
		&Controller::OnLogin);

	QObject::connect(
		&page,
		&LoginPage::GotoSignup,
		this,
		&Controller::OnGotoSignupPage);
}

void Controller::ConnectMainPage()
{
	auto& page = m_main_window.get_main_page();

	QObject::connect(
		&page,
		&MainPage::Logout,
		this,
		&Controller::OnLogout);

	QObject::connect(
		&page,
		&MainPage::ChangeSubPage,
		this,
		&Controller::OnChangeMainSubPage);

//	QObject::connect(
//		&page.get_list_create_spage(),
//		&ListsSubPage::OnListClicked,
//		this,
//		&Controller::OnChangeMainSubPage);
}

void Controller::ConnectSignupPage()
{
	auto& page = m_main_window.get_signup_page();

	QObject::connect(
		&page,
		&SignupPage::Signup,
		this,
		&Controller::OnSignup);

	QObject::connect(
		&page,
		&SignupPage::GotoLoginPage,
		this,
		&Controller::OnGotoLoginPage);
}

void Controller::Start(UIPages at_page)
{
	m_main_window.show();
	m_main_window.SetCurrentPage(at_page);
}

void Controller::StartTest()
{
	Start(UIPages::MAIN);
	m_main_window.get_main_page().SetCurrentSubPage(MainSubPages::LISTS);
}

void Controller::OnLogin(LoginInDTO in_dto)
{
	LoginModel model{m_hostname};
	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		if(response.status == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
		{
			m_main_window.get_login_page().ChangeLoginErrorLabel(
				"Login or password is incorrect");
		}
		else
		{
			QMessageBox::information(&m_main_window
				, QString("Login failed!")
				, QString::fromStdString(response.reason));
		}
		return;
	}

	auto out_dto = model.ParseResponse(response);

	m_http_client.set_auth_scheme(Net::AUTH_SCHEME_TYPE_BEARER);
	m_http_client.set_token(out_dto.token);

	SetMainSubPage(MainSubPages::LISTS);
	m_main_window.SetCurrentPage(UIPages::MAIN);
}

void Controller::OnLogout()
{
	m_http_client.ReleaseToken();
	m_main_window.SetCurrentPage(UIPages::LOGIN);
}

void Controller::SetMainSubPage(MainSubPages page)
{
	switch(page) {
	case MainSubPages::LISTS:
		UpdateMainListsSubPage();
		break;
	case MainSubPages::CREATE_LIST:
		break;
	case MainSubPages::PRODUCTS:
		break;
	case MainSubPages::ICOMES:
		break;
	case MainSubPages::SETTINGS:
		break;
	}

	m_main_window.get_main_page().SetCurrentSubPage(page);
}

void Controller::OnGotoLoginPage()
{
	m_main_window.SetCurrentPage(UIPages::LOGIN);
}

void Controller::OnChangeMainSubPage(MainSubPages page)
{
	SetMainSubPage(page);
}

void Controller::UpdateMainListsSubPage()
{
	GetListsModel model{m_hostname};
	auto request  = model.FormRequest();
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		QMessageBox::information(&m_main_window
			, QString("Error occured")
			, QString::fromStdString(response.reason));
	}

	auto lists = model.ParseResponse(response);

	auto& lists_spage = m_main_window.get_main_page().get_lists_spage();
	lists_spage.Update(lists);
}

void Controller::OnGotoSignupPage()
{
	m_main_window.SetCurrentPage(UIPages::SIGNUP);
}

void Controller::OnSignup(const SignupInDTO& in_dto)
{
	SignupModel model{m_hostname};
	if (!model.CheckPassRepeat(in_dto))
	{
		QMessageBox::warning(&m_main_window
			, QString::fromStdString("Error")
			, QString::fromStdString("Passwords must match!"));
		return;
	}

	if (!model.CheckData(in_dto))
	{
		QMessageBox::warning(&m_main_window
			, QString::fromStdString("Error")
			, QString::fromStdString("Username or password can't be empty!"));
		return;
	}

	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);

	// checking response status
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		if(response.status == Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CONFLICT)
		{
			QMessageBox::warning(&m_main_window
				, QString::fromStdString("Error")
				, QString::fromStdString("User already exists!"));
			return;
		}
	}
	m_main_window.SetCurrentPage(UIPages::LOGIN);
}
