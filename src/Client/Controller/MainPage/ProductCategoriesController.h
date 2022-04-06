
#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/CategoryEditPage/CategoryEditPage.h"
#include "View/MainPage/Product/ProductCreateSubPage/ProductCreateSubPage.h"
#include "View/MainPage/Product/ProductEditSubPage/ProductEditSubPage.h"
#include "View/MainPage/List/ListCreateSubPage/ProductQuickCreateSubPage.h"

#include "View/Constants.h"

#include "Entities/PageData.h"

class ProductCategoriesController : public QObject
{
	Q_OBJECT
public:
	explicit ProductCategoriesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		CategoryEditPage& category_edit_spag,
		ProductCreateSubPage& product_create_page,
		ProductEditSubPage& product_edit_page,
		ProductQuickCreateSubPage& product_quick_create_page);

	virtual ~ProductCategoriesController() override {}

	bool UpdateProductCategoryPage();

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

	CategoryEditPage& m_category_edit_spage;
	ProductCreateSubPage& m_product_create_page;
	ProductEditSubPage& m_product_edit_page;
	ProductQuickCreateSubPage& m_product_quick_create_page;

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void UpdatePage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);

public slots:
	void OnAddProductCategory(ProductCategory category);
	void OnDeleteProductCategory(ProductCategoryId id);
	void OnUpdateProductCategory(ProductCategory& category);
};
