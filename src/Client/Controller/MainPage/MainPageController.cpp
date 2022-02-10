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
	InitProductPagesController();
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
			m_page.get_list_create_spage(),
			m_page.get_list_view_spage(),
			m_page.get_list_edit_spage(),
			m_page.get_products_spage());

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::Message,
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

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::UpdatePage,
		this,
		&MainPageController::OnUpdateSubPage);
}

void MainPageController::InitProductPagesController()
{
	m_product_pages_controller =
		std::make_unique<ProductPagesController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_products_spage(),
			m_page.get_product_view_spage(),
			m_page.get_product_edit_spage(),
			m_page.get_product_create_spage());

	connect(
		m_product_pages_controller.get(),
		&ProductPagesController::Message,
		this,
		&MainPageController::Message);

	connect(
		m_product_pages_controller.get(),
		&ProductPagesController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_product_pages_controller.get(),
		&ProductPagesController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::OnLogout()
{
	m_http_client.ReleaseToken();
	emit ChangePage(UIPages::LOGIN);
}

void MainPageController::OnGoBack(int n)
{
	while(n)
	{
		m_history.ForgetLastPage();
		--n;
	}
	auto page = m_history.GetLastPage();
	ChangeSubPage(page);
}

void MainPageController::ChangeSubPage(MainSubPages page, PageData data)
{
	if (UpdateSubPage(page, data)) {
		m_page.SetCurrentSubPage(page);
		m_history.Update(page);
	}
	else {
		// go to error page;
	}
}

bool MainPageController::UpdateSubPage(MainSubPages page, PageData data)
{
	bool update_succeeded{true};

	switch(page)
	{
	case MainSubPages::LISTS:
		return m_list_pages_controller->UpdateListPage();
	case MainSubPages::CREATE_LIST:
		return m_list_pages_controller->UpdateListCreatePage();
	case MainSubPages::EDIT_LIST:
		return m_list_pages_controller->UpdateListEditPage(data);
	case MainSubPages::VIEW_LIST:
		return m_list_pages_controller->UpdateListViewPage(data);
	case MainSubPages::PRODUCTS:
		return m_product_pages_controller->UpdateProductsPage(data);
	case MainSubPages::VIEW_PRODUCT:
		return m_product_pages_controller->UpdateViewProductSubPage(data);
	case MainSubPages::CREATE_PRODUCT:
		break;
	case MainSubPages::EDIT_PRODUCT:
		break;
	case MainSubPages::ICOMES:
		break;
	case MainSubPages::SETTINGS:
		break;
	}

	return update_succeeded;
}

void MainPageController::OnUpdateSubPage(MainSubPages page, PageData data)
{
	UpdateSubPage(page, data);
}

void MainPageController::OnChangeSubPage(MainSubPages page, PageData data)
{
	ChangeSubPage(page, data);
}
