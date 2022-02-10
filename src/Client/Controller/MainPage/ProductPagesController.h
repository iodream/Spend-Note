#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"
#include "View/MainPage/Product/ProductViewSubPage/ProductViewSubPage.h"
#include "View/MainPage/Product/ProductEditSubPage/ProductEditSubPage.h"

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
		ProductViewSubPage& view_page,
		ProductEditSubPage& edit_page);

	virtual ~ProductPagesController() override {}

	bool UpdateProductsPage();
	bool UpdateProductsPage(List list);

	bool UpdateProductsPage(PageData data);
	bool UpdateViewProductSubPage(PageData data);

	bool UpdateViewPage(Product product);

private:
	void ConnectProductsPage();
	void ConnectViewPage();
	void ConnectEditPage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	ProductsSubPage& m_products_page;
	ProductViewSubPage& m_view_page;
	ProductEditSubPage& m_edit_page;

signals:
	void Message(const QString& window_name, const QString& message);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack();

public slots:
//	void OnGoToCreateProduct();
	void OnProductClicked(const Product& product);
	void OnEditProduct();
	void OnUpdateProduct();
};
