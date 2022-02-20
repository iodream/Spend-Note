#include "DailyListPagesController.h"

//#include "Models/"

#include "Net/Constants.h"

DailyListPagesController::DailyListPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	DailyListSubPage& dailylist_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_daily_list_page{dailylist_page}
{
	ConnectDailyListPage();
}

void DailyListPagesController::ConnectDailyListPage()
{
}
