#include "ProductCategoriesController.h"

#include "Models/Categories/Product/GetProductCategoriesModel.h"
#include "Models/Categories/Product/AddProductCategoryModel.h"
#include "Models/Categories/Product/UpdateProductCategoryModel.h"
#include "Models/Categories/Product/RemoveProductCategoryModel.h"


#include "Net/Constants.h"

ProductCategoriesController::ProductCategoriesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	CategoryEditPage& category_edit_spage,
	ProductCreateSubPage& product_create_page,
	ProductEditSubPage& product_edit_page,
	ProductQuickCreateSubPage& product_quick_create_page):
	m_http_client(http_client),
	m_hostname(hostname),
	m_user_id(user_id),
	m_category_edit_spage(category_edit_spage),
	m_product_create_page(product_create_page),
	m_product_edit_page(product_edit_page),
	m_product_quick_create_page(product_quick_create_page)
{
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::AddProductCategory,
		this,
		&ProductCategoriesController::OnAddProductCategory);
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::RemoveProductCategory,
		this,
		&ProductCategoriesController::OnDeleteProductCategory);
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::UpdateProductCategory,
		this,
		&ProductCategoriesController::OnUpdateProductCategory);
	connect(
		&m_product_create_page,
		&ProductCreateSubPage::AddProductCategory,
		this,
		&ProductCategoriesController::OnAddProductCategory);
	connect(
		&m_product_edit_page,
		&ProductEditSubPage::AddProductCategory,
		this,
		&ProductCategoriesController::OnAddProductCategory);
	connect(
		&m_product_quick_create_page,
		&ProductQuickCreateSubPage::AddProductCategory,
		this,
		&ProductCategoriesController::OnAddProductCategory);
}

bool ProductCategoriesController::UpdateProductCategoryPage()
{
	GetProductCategoriesModel model{m_hostname};
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

	auto categories = model.ParseResponse(response);
	m_category_edit_spage.Update(categories);

	return true;
}



void ProductCategoriesController::OnAddProductCategory(ProductCategory category)
{
	AddProductCategoryModel model{m_hostname};
	category.id = 0;

	if(!model.CheckFields(category))
	{
		emit ClientError("Fields can't be empty!");
		return;
	}

	auto request  = model.FormRequest(m_user_id, category);

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
		return;
	}
	UpdateProductCategoryPage();
}


void ProductCategoriesController::OnDeleteProductCategory(ProductCategoryId id)
{
	RemoveProductCategoryModel model{m_hostname};

	auto request  = model.FormRequest(id);

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
		return;
	}
	UpdateProductCategoryPage();
}

void ProductCategoriesController::OnUpdateProductCategory(ProductCategory& category)
{
	UpdateProductCategoryModel model{m_hostname};

	auto request  = model.FormRequest(category);

//	if(!model.CheckFields(category))
//	{
//		emit ClientError("Fields can't be empty!");
//		return;
//	}

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
		return;
	}
	UpdateProductCategoryPage();
}
