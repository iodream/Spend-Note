#include "DailyListPageController.h"

DailyListPageController::DailyListPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	DailyListSubPage& daily_list_page)
	: m_http_client(http_client)
	, m_hostname(hostname)
	, m_user_id(user_id)
	, m_daily_list_page(daily_list_page)
{
	ConnectDailyListPage();
}

void DailyListPageController::ConnectDailyListPage()
{
	connect(
		&m_daily_list_page,
		&DailyListSubPage::GoToProductView,
		this,
		&DailyListPageController::OnGoToProductView);
}

void DailyListPageController::OnGoToProductView(const Product& product)
{
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PRODUCT, data);
}

bool DailyListPageController::UpdateDailyListPage()
{
	GetDailyListModel model{m_hostname};
	auto request = model.FormRequest(m_user_id);

	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch (Poco::Exception& exc)
	{
		return false;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto list = model.ParseResponse(response);
	m_daily_list_page.Update(list);

	return true;
}
