#include "Controller.h"

#include "Models/LoginModel.h"
#include "Models/List/GetListsModel.h"

#include "Net/Constants.h"

Controller::Controller()
{
	ConnectLoginPage();
	ConnectMainPage();
}

void Controller::ConnectLoginPage()
{
	auto& page = m_main_window.get_login_page();

	QObject::connect(
		&page,
		&LoginPage::Login,
		this,
		&Controller::OnLogin);
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

void Controller::OnLogin(LoginModel::JSONFormatter::Credentials credentials)
{
	LoginModel model{m_hostname};
	auto request  = model.FormRequest(credentials);
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

	auto token = model.ParseResponse(response);

	m_http_client.set_auth_scheme(Net::AUTH_SCHEME_TYPE_BEARER);
	m_http_client.set_token(token.token);

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
