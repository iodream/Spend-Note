#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"

#include "Entities/PageData.h"

#include "View/Constants.h"

class ProductPagesController : public QObject
{
	Q_OBJECT
public:
	ProductPagesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		ProductsSubPage& list_page);

	virtual ~ProductPagesController() override {};

	bool UpdateListPage();
	bool UpdateListPage(List list);

private:
	void ConnectListPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	ProductsSubPage& m_list_page;

signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack();

public slots:
//	void OnGoToCreateProduct();
};
