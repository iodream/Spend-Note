#include "Controller.h"

#include "Net/Constants.h"

Controller::Controller()
{
	QObject::connect(
		&m_main_window.get_login_page(),
		&LoginPage::Login,
		this,
		&Controller::OnLogin);

	QObject::connect(
		&m_main_window.get_main_page(),
		&MainPage::Logout,
		this,
		&Controller::OnLogout);
//	QObject::connect(
//		&m_main_window.m_main_page.m_lists_page,
//		&ListsPage::GetLists,
//		this,
//		&Controller::OnGetLists);
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
	LoginModel model;
	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);

	// checking response status
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


	m_main_window.SetCurrentPage(UIPages::MAIN);
}

void Controller::OnGetLists()
{
	ListsModel model;
	ListInDTO in_dto;
	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);

	// checking response status
	// check if status ok
	// errorstatus
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		if(response.status == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
		{
			m_main_window.m_login_page.ChangeLoginErrorLabel(
					"Login and password do not match");
		}
		else
		{
			QMessageBox::information(&m_main_window
					, QString::fromStdString("Login failed!")
					, QString::fromStdString(response.reason));
		}
		return;
	}

	auto out_dto = model.ParseResponse(response);
//ok
//use alias to make shorter

	//m_main_window.m_main_page.m_lists_page.UpdateData(out_dto);
}

void Controller::OnLogout()
{
	m_http_client.ReleaseToken();
	m_main_window.SetCurrentPage(UIPages::LOGIN);
}
