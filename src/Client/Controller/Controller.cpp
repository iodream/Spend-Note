#include "Controller.h"

#include "Net/Constants.h"

Controller::Controller()
{
    QObject::connect(
		&m_main_window.m_login_page, &LoginPage::Login,
		this, &Controller::OnLogin);
}

void Controller::Start(UIPages at_page)
{
	m_main_window.show();
	m_main_window.SetCurrentPage(at_page);
}

void Controller::StartTest()
{
	Start(UIPages::MAIN);
	m_main_window.m_main_page.AddListSubPage("Some list 1", 1);
	m_main_window.m_main_page.AddListSubPage("Some list 2", 2);
	m_main_window.m_main_page.AddListSubPage("Some list 3", 3);
	m_main_window.m_main_page.RemoveListSubPage(3);
	m_main_window.m_main_page.SetCurrentSubPageList(2);
}

void Controller::OnLogin(LoginInDTO in_dto)
{
	LoginModel model;
	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);
	// there i should check response status
	// but now i think that everything is ok
	auto out_dto = model.ParseResponse(response);

	m_http_client.set_auth_scheme(Net::AUTH_SCHEME_TYPE_BEARER);
	m_http_client.set_token(out_dto.token);

	// there i could set new data to the page

	m_main_window.SetCurrentPage(UIPages::MAIN);
}
