#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"
#include "View/MainPage/Product/ProductViewSubPage/ProductViewSubPage.h"
#include "View/MainPage/Product/ProductCreateSubPage/ProductCreateSubPage.h"
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
		ProductEditSubPage& edit_page,
		ProductCreateSubPage& create_page);

	virtual ~ProductPagesController() override {}

	bool UpdateProductsPage();
	bool UpdateProductsPage(List list);

	bool UpdateProductsPage(PageData data);
	bool UpdateViewProductSubPage(PageData data);

	bool UpdateViewPage(Product product);

	void SetRangeOfSpinBoxes();
	void UpdateCategoryBox();

private:
	void ConnectProductsPage();
	void ConnectViewPage();
	void ConnectEditPage();
	void ConnectCreatePage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;
	IdType m_list_id;

	ProductsSubPage& m_products_page;
	ProductViewSubPage& m_view_page;
	ProductEditSubPage& m_edit_page;
	ProductCreateSubPage& m_create_page;

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack(int n=1);

public slots:
	void OnProductClicked(const Product& product);
	void OnEditProduct();
	void OnUpdateProduct();
	void OnGoToCreateProduct(IdType list_id);
	void OnCreateProduct();
	void OnDeleteProduct();
};
