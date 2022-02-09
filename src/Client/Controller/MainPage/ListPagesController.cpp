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
}

void ListPagesController::ConnectListPage()
{
	connect(
		&m_list_page,
		&ListsSubPage::GoToCreateList,
		this,
		&ListPagesController::OnGoToCreateList);
	connect(
		&m_list_page,
		&ListsSubPage::GoToProducts,
		this,
		&ListPagesController::OnGoToProducts);
}

void ListPagesController::ConnectCreatePage()
{
	connect(
		&m_create_page,
		&ListCreateSubPage::GoBack,
		this,
		&ListPagesController::GoBack);

	connect(
	&m_create_page,
	&ListCreateSubPage::CreateList,
	this,
	&ListPagesController::OnCreateList);
}

bool ListPagesController::UpdateListPage()
{
	GetListsModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id);

	Net::Response response;
	try{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
			return false;
	}
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

void ListPagesController::OnCreateList()
{
	AddNewListsModel model{m_hostname};

	List new_list;
	new_list.name = m_create_page.GetListName();
	new_list.id = 0;
	new_list.owner_id = m_user_id;

	ListState state;
	state.id = 1;
	state.name = QString("");
	new_list.state = state;

	if(!model.CheckName(new_list.name))
	{
		emit Message(
				QString("Error!"),
				QString("List name can't be empty")
				);
		return;
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

	emit GoBack();
}

void ListPagesController::OnGoToProducts(const List& list)
{
	PageData data{};
	data.setValue(list);
	emit ChangeSubPage(MainSubPages::PRODUCTS, data);
}
