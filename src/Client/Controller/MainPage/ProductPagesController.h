#pragma once

#include "Controller/HTTPClient.h"

#include "View/MainPage/Product/ProductsSubPage/ProductsSubPage.h"
#include "View/MainPage/Product/ProductViewSubPage/ProductViewSubPage.h"
#include "View/MainPage/Product/ProductCreateSubPage/ProductCreateSubPage.h"
#include "View/MainPage/Product/ProductEditSubPage/ProductEditSubPage.h"
#include "View/MainPage/Product/PeriodicProductCreateSubPage/PeriodicProductCreateSubPage.h"
#include "View/MainPage/Product/PeriodicProductEditSubPage/PeriodicProductEditSubPage.h"
#include "View/MainPage/Product/PeriodicProductViewSubPage/PeriodicProductViewSubPage.h"

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
		ProductCreateSubPage& create_page,
		PeriodicProductCreateSubPage& periodic_create_page,
		PeriodicProductEditSubPage& periodic_edit_page,
		PeriodicProductViewSubPage& periodic_view_page);

	virtual ~ProductPagesController() override {}

	bool UpdateProductsPage();
	bool UpdateProductsPage(List list);

	bool UpdateProductsPage(PageData data);
	bool UpdateViewProductSubPage(PageData data);

	bool UpdateViewPage(Product product);
	void UpdateProductColors();

	bool UpdatePeriodicProductsPage(PageData data);
	bool UpdatePeriodicProductsPage();
	bool UpdatePeriodicProductsPage(List list);

	void SetRangeOfSpinBoxes();
	void UpdateCategoryBox();

private:
	void ConnectProductsPage();
	void ConnectViewPage();
	void ConnectEditPage();
	void ConnectCreatePage();

	void ConnectPeridoicViewPage();
	void ConnectPeriodicEditPage();
	void ConnectPeriodicCreatePage();

	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;
	IdType m_list_id;

	ProductsSubPage& m_products_page;
	ProductViewSubPage& m_view_page;
	ProductEditSubPage& m_edit_page;
	ProductCreateSubPage& m_create_page;

	PeriodicProductCreateSubPage& m_periodic_create_page;
	PeriodicProductEditSubPage& m_periodic_edit_page;
	PeriodicProductViewSubPage& m_periodic_view_page;

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const QString& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void GoBack(int n=1);

public slots:
	void OnProductClicked(const Product& product);
	void OnEditProduct();
	void OnUpdateProduct();
	void OnGoToCreateProduct(IdType list_id);
	void OnCreateProduct();
	void OnDeleteProduct();

	void OnPeriodicProductCliked(const PeriodicProduct& product);
	void OnEditPeriodicProduct();
	void OnUpdatePeriodicProduct();
	void OnGoToCreatePeriodicProduct(IdType list_id);
	void OnCreatePeriodicProduct();
	void OnDeletePeriodicProduct();
};
