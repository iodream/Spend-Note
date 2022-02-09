#include "ListCreatePageController.h"
#include "Models/List/AddNewListModel.h"
#include "Net/Constants.h"
#include "View/MainPage/List/ListCreateSubPage/ListCreateSubPage.h"

ListCreatePageController::ListCreatePageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		ListsSubPage& list_page,
		ListCreateSubPage& create_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_list_page{list_page}
	, m_create_page{create_page}
{

	ConnectCreatePage();
}

void ListCreatePageController::ConnectCreatePage()
{

}


