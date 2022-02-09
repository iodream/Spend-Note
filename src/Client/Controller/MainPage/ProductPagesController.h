#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"
#include "View/MainPage/Product/ProductViewSubPage/ProductViewSubPage.h"

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
		ProductsSubPage& products_page,
		ProductViewSubPage& view_page);

	virtual ~ProductPagesController() override {}

	bool UpdateListPage();
	bool UpdateListPage(List list);

	bool UpdateViewPage(Product product);

private:
	void ConnectProductsPage();
	void ConnectViewPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	ProductsSubPage& m_products_page;
	ProductViewSubPage& m_view_page;

signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack();

public slots:
//	void OnGoToCreateProduct();
	void OnProductClicked(const Product& product);
};
