#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/List/ListsSubPage/ListsSubPage.h"
#include "View/MainPage/List/ListCreateSubPage/ListCreateSubPage.h"
#include "View/MainPage/List/ListViewSubPage/ListViewSubPage.h"
#include "View/MainPage/List/ListEditSubPage/ListEditSubPage.h"
#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"
#include "View/Constants.h"

#include "Entities/PageData.h"

class ListPagesController : public QObject
{
	Q_OBJECT
public:
	ListPagesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		ListsSubPage& list_page,
		ListCreateSubPage& create_page,
		ListViewSubPage& list_view_page,
		ListEditSubPage& list_edit_page,
		ProductsSubPage& product_page);

	virtual ~ListPagesController() override {}

	bool UpdateListPage();
	bool UpdateListCreatePage();
	bool UpdateListViewPage(PageData& data);
	bool UpdateListEditPage(PageData& data);

private:
	void ConnectListPage();
	void ConnectCreatePage();
	void ConnectViewListPage();
	void ConnectEditListPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	ListsSubPage& m_list_page;
	ListCreateSubPage& m_create_page;
	ListViewSubPage& m_list_view_page;
	ListEditSubPage& m_list_edit_page;
	ProductsSubPage& m_product_page;

	void FillBoxOfStates();
	static bool already_added;

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);
	void CreateList();

public slots:
	void OnGoToProducts(const List& list);
	void OnUpdateList();
	void OnDeleteList(const List& list);
	void OnGoToViewList();
	void OnGoToEditList();
	void OnGoToCreateList();
	void OnCreateList();
};
