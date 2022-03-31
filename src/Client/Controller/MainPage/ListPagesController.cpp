#include "ListPagesController.h"

#include "Models/List/GetListsModel.h"
#include "Models/List/AddNewListModel.h"
#include "Models/List/RemoveListModel.h"
#include "Models/List/UpdateListModel.h"
#include "Models/Product/AddProductModel.h"
#include "Models/Product/GetProductCategoriesModel.h"

#include "View/MainPage/List/ListCreateSubPage/Item.h"
#include "Models/List/GetListStatesModel.h"

#include "Net/Constants.h"

ListPagesController::ListPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ListsSubPage& list_page,
	ListCreateSubPage& create_page,
	ListViewSubPage& list_view_page,
	ListEditSubPage& list_edit_page,
	ProductsSubPage& product_page,
	ProductQuickCreateSubPage& product_quick_create_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_list_page{list_page}
	, m_create_page{create_page}
	, m_list_view_page{list_view_page}
	, m_list_edit_page{list_edit_page}
	, m_product_page{product_page}
	, m_product_quick_create_page{product_quick_create_page}
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
	connect(
		&m_create_page,
		&ListCreateSubPage::GoToQuickCreateProduct,
		this,
		&ListPagesController::OnGoToQuickCreateProduct);
	connect(
		&m_product_quick_create_page,
		&ProductQuickCreateSubPage::QuickAddItem,
		this,
		&ListPagesController::OnQuickAddItem);
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
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto lists = model.ParseResponse(response);

	m_list_page.Update(lists);

	FillBoxOfStates();
	return true;
}

bool ListPagesController::UpdateListCreatePage()
{
	m_create_page.Update();
	return true;
}

bool ListPagesController::UpdateListQuickCreatePage()
{
	UpdateCategoryBox();
	SetRangeOfSpinBoxes();
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

bool ListPagesController::already_added = false;

void ListPagesController::FillBoxOfStates()
{
	if(!already_added)
	{
		GetListStatesModel model{m_hostname};
		const auto request = model.FormRequest();
		try
		{
			auto response = m_http_client.Request(request);

			if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
			{
				emit ServerError(response.status, response.reason);
				return ;
			}

			auto states = model.ParseResponse(response);
			m_list_edit_page.FillStateBox(states);
			m_create_page.FillStateBox(states);
			already_added = true;
		}
		catch(const Poco::Exception& ex)
		{
			return;
		}
	}
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
	new_list.state.id = m_create_page.GetListState();
	new_list.id = 0;
	new_list.owner_id = m_user_id;
	if(!model.CheckName(new_list.name))
	{
		emit ClientError("List name can't be empty");
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
		emit ServerError(response.status, response.reason);
		return ;
	}

	auto lists = model.ParseResponse(response);

	//if there are any products in create new list subpage product list, add them
	for(auto& new_product: m_create_page.GetItems())
	{
		new_product.list_id = lists.id; //get list id here after it was added

		AddProductModel model{m_hostname};

		if(!model.CheckFields(new_product))
		{
			emit ClientError("Product data can't be empty");
			return;
		}
		auto request  = model.FormRequest(new_product);

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
			emit ServerError(response.status, response.reason);
			return ;
		}
	}

	m_create_page.ClearItems(); //clear page and items
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
	m_create_page.ClearItems();
	FillBoxOfStates();
	emit ChangeSubPage(MainSubPages::CREATE_LIST);
}

void ListPagesController::OnGoToQuickCreateProduct()
{
	emit ChangeSubPage(MainSubPages::QUICK_CREATE_PRODUCT);
}

//adds new products to the vector and widget list on CreateNewList subpage
void ListPagesController::OnQuickAddItem()
{
	Product new_item;
	new_item.name = m_product_quick_create_page.GetName();
	new_item.is_bought = m_product_quick_create_page.GetIsBought();
	new_item.amount = m_product_quick_create_page.GetAmount();
	new_item.buy_until_date = m_product_quick_create_page.GetBuyUntil();
	new_item.price = m_product_quick_create_page.GetPrice();
	new_item.priority = m_product_quick_create_page.GetPriority();
	new_item.category.id = m_product_quick_create_page.GetCategoryId();
	new_item.category.name = m_product_quick_create_page.GetCategoryName();
	new_item.add_date = QDateTime::currentDateTime().toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	new_item.purchase_date = "";

	if(!AddProductModel::CheckFields(new_item))
	{
		emit ClientError("Product data can't be empty");
		return;
	}

	m_create_page.AddProductToVector(new_item);
	Item* item = new Item(QString(new_item.name));
	m_create_page.AppendItem(item);

	emit GoBack();
}
int ListPagesController::m_curr_products = 0;
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
		emit ServerError(response.status, response.reason);
		return ;
	}

	emit GoBack(2); // go back 2 pages to avoid sending another request to the server
}

void ListPagesController::OnUpdateList()
{
	UpdateListModel model{m_hostname};

	List list = m_list_edit_page.get_list();

	if(!model.CheckName(list.name))
	{
		emit ClientError("List name can't be empty");
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
		emit ServerError(response.status, response.reason);
		return ;
	}

	PageData data;
	data.setValue(list);

	emit UpdatePage(MainSubPages::PRODUCTS, data);
	emit UpdatePage(MainSubPages::VIEW_LIST, data);
	emit GoBack();
}

bool ListPagesController::category_already_added = false;

void ListPagesController::UpdateCategoryBox()
{
	if(!category_already_added)
	{
		GetProductCategoriesModel model{m_hostname};
		auto request = model.FormRequest();

		try
		{
			auto response = m_http_client.Request(request);

			if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
			{
				emit ServerError(response.status, response.reason);
				return ;
			}
			m_product_quick_create_page.FillCategoryBox(model.ParseResponse(response));
			category_already_added = true;
		}
		catch (const Poco::Exception& ex)
		{
			return;
		}

	}
}


void ListPagesController::SetRangeOfSpinBoxes()
{
	m_product_quick_create_page.SetRangeOfSpinBox();
}
