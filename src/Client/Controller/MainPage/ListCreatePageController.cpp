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
	connect(
	&m_create_page,
	&ListCreateSubPage::CreateList,
	this,
	&ListCreatePageController::OnCreateList);
}

//checks data and sends request
void ListCreatePageController::OnCreateList()
{
	AddNewListsModel model{m_hostname};

	List new_list;
	new_list.name = m_create_page.GetListName();
	new_list.id = m_list_page.get_list_size() + 1;
	new_list.owner_id = m_user_id;

	ListState state;
	state.id = 1;
	state.name = QString("active");
	new_list.state = state;

	if(!model.CheckName(new_list.name))
	{
		emit Message(
				QString("Error!"),
				QString("List name cannot be empty")
				);
		return; //abort
	}

	auto request  = model.FormRequest(new_list, m_user_id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error!"),
			QString::fromStdString(response.reason));
		return ;
	}

	auto lists = model.ParseResponse(response);

	emit GoBack(); //immediately go to previous page
}
