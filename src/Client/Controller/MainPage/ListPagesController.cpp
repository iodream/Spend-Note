#include "ListPagesController.h"

#include "Models/List/GetListsModel.h"
#include "Models/List/AddNewListModel.h"

#include "Net/Constants.h"

ListPagesController::ListPagesController(
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
	ConnectListPage();
	ConnectCreatePage();
	InitCreatePageController();
}

void ListPagesController::InitCreatePageController()
{
	m_list_create_page_controller =
		std::make_unique<ListCreatePageController>(
			m_http_client,
			m_hostname,
			m_user_id,
			m_list_page,
			m_create_page);
}

void ListPagesController::ConnectListPage()
{
	connect(
		&m_list_page,
		&ListsSubPage::GoToCreateList,
		this,
		&ListPagesController::OnGoToCreateList);
}

void ListPagesController::ConnectCreatePage()
{
	connect(
		&m_create_page,
		&ListCreateSubPage::GoBack,
		this,
		&ListPagesController::GoBack);
}

bool ListPagesController::UpdateListPage()
{
	GetListsModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return false;
	}

	auto lists = model.ParseResponse(response);

	m_list_page.Update(lists);
	return true;
}

void ListPagesController::OnGoToCreateList()
{
	emit ChangeSubPage(MainSubPages::CREATE_LIST);
}
