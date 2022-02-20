#include "ListPagesController.h"

#include "Models/List/GetListsModel.h"
#include "Models/List/AddNewListModel.h"
#include "Models/List/RemoveListModel.h"
#include "Models/List/UpdateListModel.h"

#include "Net/Constants.h"

ListPagesController::ListPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ListsSubPage& list_page,
	ListCreateSubPage& create_page,
	ListViewSubPage& list_view_page,
	ListEditSubPage& list_edit_page,

	ProductsSubPage& product_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_list_page{list_page}
	, m_create_page{create_page}
	, m_list_view_page{list_view_page}
	, m_list_edit_page{list_edit_page}
	, m_product_page{product_page}
{
	ConnectListPage();
	ConnectCreatePage();
	ConnectViewListPage();
	ConnectEditListPage();
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
		&ListCreateSubPage::CreateList,
		this,
		&ListPagesController::OnCreateList);
}

void ListPagesController::ConnectViewListPage()
{
	connect(
		&m_product_page,
		&ProductsSubPage::GoToViewList,
		this,
		&ListPagesController::OnGoToViewList);
	connect(
		&m_list_view_page,
		&ListViewSubPage::DeleteList,
		this,
		&ListPagesController::OnDeleteList);
}

void ListPagesController::ConnectEditListPage()
{
	connect(
		&m_list_view_page,
		&ListViewSubPage::GoToEditList,
		this,
		&ListPagesController::OnGoToEditList);
	connect(
		&m_list_edit_page,
		&ListEditSubPage::UpdateList,
		this,
		&ListPagesController::OnUpdateList);
	connect(
		&m_list_edit_page,
		&ListEditSubPage::UpdateListView,
		this,
		&ListPagesController::UpdateListViewPage);
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
		emit Error(response.status, response.reason);
		return false;
	}

	auto lists = model.ParseResponse(response);

	m_list_page.Update(lists);
	return true;
}

bool ListPagesController::UpdateListCreatePage()
{
	m_create_page.Update();
	return true;
}

bool ListPagesController::UpdateListViewPage(PageData& data)
{
	if (!data.canConvert<List>()) {
		return true;
	}
	auto list = qvariant_cast<List>(data);
	m_list_view_page.Update(list);
	return true;
}

bool ListPagesController::UpdateListEditPage(PageData& data)
{
	if (!data.canConvert<List>()) {
		return true;
	}
	auto list = qvariant_cast<List>(data);
	m_list_edit_page.Update(list);
	return true;
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
		emit Error(
			static_cast<int>(ErrorCodes::EMPTY_FIELD),
			"List name can't be empty");
		return;
	}

	auto request  = model.FormRequest(new_list, m_user_id);

	Net::Response response;
	try{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Error(response.status, response.reason);
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

void ListPagesController::OnGoToViewList()
{
	auto list = m_product_page.get_list();
	PageData data{};
	data.setValue(list);
	emit ChangeSubPage(MainSubPages::VIEW_LIST, data);
}

void ListPagesController::OnGoToCreateList()
{
	emit ChangeSubPage(MainSubPages::CREATE_LIST);
}

void ListPagesController::OnGoToEditList()
{
	auto list = m_product_page.get_list();
	PageData data{};
	data.setValue(list);
	emit ChangeSubPage(MainSubPages::EDIT_LIST, data);
}

void ListPagesController::OnDeleteList(const List& list)
{
	RemoveListModel model{m_hostname};
	ListId elem;
	elem.id = list.id;

	auto request  = model.FormRequest(elem);
	Net::Response response;
	try{
	response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Error(response.status, response.reason);
		return ;
	}

	emit GoBack(2); // go back 2 pages to avoid sending another request to the server
}

void ListPagesController::OnUpdateList(const List& list)
{
	UpdateListModel model{m_hostname};

	if(!model.CheckName(list.name))
	{
		emit Error(
			static_cast<int>(ErrorCodes::EMPTY_FIELD),
			"List name can't be empty");
		return;
	}

	auto request  = model.FormRequest(list);

	Net::Response response;
	try{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit Error(response.status, response.reason);
		return ;
	}

	PageData data;
	data.setValue(list);

	emit UpdatePage(MainSubPages::PRODUCTS, data);
	emit UpdatePage(MainSubPages::VIEW_LIST, data);
	emit GoBack();
}
