#include "MainPageController.h"

#include "Net/Constants.h"

MainPageController::MainPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	MainPage& page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_page{page}
{
	ConnectPage();
	InitListPagesController();
}

void MainPageController::ConnectPage()
{
	QObject::connect(
		&m_page,
		&MainPage::Logout,
		this,
		&MainPageController::OnLogout);

	QObject::connect(
		&m_page,
		&MainPage::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	QObject::connect(
		&m_page,
		&MainPage::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitListPagesController()
{
	m_list_pages_controller =
		std::make_unique<ListPagesController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_lists_spage(),
			m_page.get_list_create_spage());

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::Message,
		this,
		&MainPageController::Message);

	connect(
		m_list_pages_controller->m_list_create_page_controller.get(),
		&ListCreatePageController::Message,
		this,
		&MainPageController::Message);

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::OnLogout()
{
	m_http_client.ReleaseToken();
	emit ChangePage(UIPages::LOGIN);
}

void MainPageController::OnGoBack()
{
	m_history.ForgetLastPage();
	auto page = m_history.GetLastPage();
	ChangeSubPage(page);
}

void MainPageController::ChangeSubPage(MainSubPages page)
{
	bool update_succeeded{true};

	switch(page) {
	case MainSubPages::LISTS:
		update_succeeded = m_list_pages_controller->UpdateListPage();
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

	if (update_succeeded) {
		m_page.SetCurrentSubPage(page);
		m_history.Update(page);
	}
	else {
		// go to error page;
	}
}

void MainPageController::OnChangeSubPage(MainSubPages page)
{
	ChangeSubPage(page);
}
