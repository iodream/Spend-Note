#include "MainPageController.h"

#include "Net/Constants.h"

#include "View/MainPage/List/ListCreateSubPage/ProductQuickCreateSubPage.h"

#include "Models/Statistics/GetBalanceModel.h"

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
	InitIncomePagesController();
	InitDailyListPageController();
	InitStatisticsPageController();
	InitIncomeCategoriesController();
	InitProductCategoriesController();
	InitSettingsPageController();
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
			m_page.get_products_spage(),
			m_page.get_product_quick_create_spage());

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_list_pages_controller.get(),
		&ListPagesController::ClientError,
		this,
		&MainPageController::OnClientError);

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

//	connect(
//		m_list_pages_controller.get(),
//		&ListPagesController::CreateProduct,
//		m_product_pages_controller.get,
//		&ProductPagesController::OnCreateProduct);
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
		&ProductPagesController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_product_pages_controller.get(),
		&ProductPagesController::ClientError,
		this,
		&MainPageController::OnClientError);

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

void MainPageController::InitIncomePagesController()
{
	m_income_pages_controller =
		std::make_unique<IncomePagesController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_incomes_spage(),
			m_page.get_incomes_create_spage(),
			m_page.get_income_view_spage(),
			m_page.get_income_edit_spage());

	connect(
		m_income_pages_controller.get(),
		&IncomePagesController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_income_pages_controller.get(),
		&IncomePagesController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_income_pages_controller.get(),
		&IncomePagesController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_income_pages_controller.get(),
		&IncomePagesController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitDailyListPageController()
{
	m_daily_list_page_controller =
		std::make_unique<DailyListPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_daily_list_spage());

	connect(
		m_daily_list_page_controller.get(),
		&DailyListPageController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_daily_list_page_controller.get(),
		&DailyListPageController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_daily_list_page_controller.get(),
		&DailyListPageController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_daily_list_page_controller.get(),
		&DailyListPageController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitStatisticsPageController()
{
	m_statistics_page_controller =
		std::make_unique<StatisticsPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_statistics_spage());

	connect(
		m_statistics_page_controller.get(),
		&StatisticsPageController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_statistics_page_controller.get(),
		&StatisticsPageController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_statistics_page_controller.get(),
		&StatisticsPageController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_statistics_page_controller.get(),
		&StatisticsPageController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitIncomeCategoriesController()
{
	m_income_categories_controller =
		std::make_unique<IncomeCategoriesController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_incomes_create_spage(),
			m_page.get_income_edit_spage(),
			m_page.get_categories_edit_spage());

	connect(
		m_income_categories_controller.get(),
		&IncomeCategoriesController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_income_categories_controller.get(),
		&IncomeCategoriesController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_income_categories_controller.get(),
		&IncomeCategoriesController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitProductCategoriesController()
{
	m_product_categories_controller =
		std::make_unique<ProductCategoriesController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_product_create_spage(),
			m_page.get_product_edit_spage(),
			m_page.get_product_quick_create_spage(),
			m_page.get_categories_edit_spage());

	connect(
		m_product_categories_controller.get(),
		&ProductCategoriesController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_product_categories_controller.get(),
		&ProductCategoriesController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_product_categories_controller.get(),
		&ProductCategoriesController::GoBack,
		this,
		&MainPageController::OnGoBack);
}

void MainPageController::InitSettingsPageController()
{
	m_settings_page_controller =
		std::make_unique<SettingsPageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_page.get_settings_spage());

	connect(
		m_settings_page_controller.get(),
		&SettingsPageController::ServerError,
		this,
		&MainPageController::OnServerError);

	connect(
		m_settings_page_controller.get(),
		&SettingsPageController::ClientError,
		this,
		&MainPageController::OnClientError);

	connect(
		m_settings_page_controller.get(),
		&SettingsPageController::ChangeSubPage,
		this,
		&MainPageController::OnChangeSubPage);

	connect(
		m_settings_page_controller.get(),
		&SettingsPageController::GoBack,
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
	MainSubPages page;
	try{
		page = m_history.GetLastPage();
	}
	catch(const std::out_of_range& exc)
	{
		qDebug() << exc.what();
		page = MainSubPages::LISTS;
	}

	ChangeSubPage(page);
}

void MainPageController::ChangeSubPage(MainSubPages page, PageData data)
{
	if (UpdateSubPage(page, data)) {
		m_page.SetCurrentSubPage(page);
		m_history.Update(page);
	}
	else {
		m_page.SetErrorBanner("Error updating page");
	}
}

void MainPageController::OnServerError(const int code, const std::string& desc)
{
	m_page.SetErrorBanner(code, desc);
}

void MainPageController::OnClientError(const std::string& desc)
{
	m_page.SetErrorBanner(desc);
}

bool MainPageController::UpdateSubPage(MainSubPages page, PageData data)
{
	bool update_succeeded{true};

	m_page.ShowBalance(*UpdateUserBalance(m_user_id));

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
	case MainSubPages::INCOMES:
		return m_income_pages_controller->UpdateIncomesPage();
	case MainSubPages::VIEW_INCOME:
		return m_income_pages_controller->UpdateIncomeViewPage(data);
	case MainSubPages::EDIT_INCOME:
		return m_income_pages_controller->UpdateIncomeEditPage(data);
	case MainSubPages::SETTINGS:
		m_settings_page_controller->UpdateSettingsSubPage();
		break;
	case MainSubPages::DAILY_LIST:
		return m_daily_list_page_controller->UpdateDailyListPage();
	case MainSubPages::QUICK_CREATE_PRODUCT:
		return m_list_pages_controller->UpdateListQuickCreatePage();
	case MainSubPages::STATISTICS:
		return m_statistics_page_controller->UpdateStatisticsPage();
	case MainSubPages::CATEGORIES_EDIT:
		m_income_categories_controller->UpdateIncomeCategoryPage();
		return m_product_categories_controller->UpdateProductCategoryPage();
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

std::optional<Balance> MainPageController::UpdateUserBalance(const IdType &id)
{
	GetBalanceModel model{m_hostname};
	auto request = model.FormRequest(id);

	try
	{
		auto response = m_http_client.Request(request);

		if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
		{
			m_page.SetErrorBanner(response.status, response.reason);
			return std::nullopt;
		}

		return model.ParseResponse(response);
	}
	catch(const Poco::Exception& ex)
	{
		return std::nullopt;
	}

}
