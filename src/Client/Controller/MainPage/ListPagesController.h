#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/List/ListsSubPage/ListsSubPage.h"
#include "View/MainPage/List/ListCreateSubPage/ListCreateSubPage.h"
#include "Common.h"
#include "View/Constants.h"
#include "Controller/MainPage/ListCreatePageController.h"

class ListPagesController : public QObject
{
	Q_OBJECT
public:
	ListPagesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		ListsSubPage& list_page,
		ListCreateSubPage& create_page);

	virtual ~ListPagesController() override {}

	bool UpdateListPage();

	std::unique_ptr<ListCreatePageController> m_list_create_page_controller;

private:
	void ConnectListPage();
	void ConnectCreatePage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	ListsSubPage& m_list_page;
	ListCreateSubPage& m_create_page;
	void InitCreatePageController();


signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page);
	void GoBack();
	void CreateList();

public slots:
	void OnGoToCreateList();
};
