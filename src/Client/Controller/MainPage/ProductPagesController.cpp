#include "ProductPagesController.h"

#include "Models/Product/GetProductsModel.h"
#include "Models/Product/UpdateProductModel.h"
#include "Models/Product/AddProductModel.h"
#include "Models/Product/RemoveProductModel.h"
#include "Models/Categories/Product/GetProductCategoriesModel.h"
#include "Models/PeriodicProduct/AddPeriodicProductModel.h"
#include "Models/PeriodicProduct/GetPeriodicProductsModel.h"
#include "Models/PeriodicProduct/RemovePeriodicProductModel.h"
#include "Models/PeriodicProduct/UpdatePeriodicProductModel.h"

#include "Net/Constants.h"

ProductPagesController::ProductPagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	ProductsSubPage& products_page,
	ProductViewSubPage& view_page,
	ProductEditSubPage& edit_page,
	ProductCreateSubPage& create_page,
	PeriodicProductCreateSubPage& periodic_create_page,
	PeriodicProductEditSubPage& periodic_edit_page,
	PeriodicProductViewSubPage& periodic_view_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_products_page{products_page}
	, m_view_page{view_page}
	, m_edit_page{edit_page}
	, m_create_page{create_page}
	, m_periodic_create_page{periodic_create_page}
	, m_periodic_edit_page{periodic_edit_page}
	, m_periodic_view_page{periodic_view_page}
{
	ConnectProductsPage();
	ConnectViewPage();
	ConnectEditPage();
	ConnectCreatePage();
	ConnectPeriodicEditPage();
	ConnectPeriodicCreatePage();
	ConnectPeriodicViewPage();
}

bool ProductPagesController::UpdateProductsPage(PageData data)
{
	if (!data.canConvert<List>())
	{
		bool a = UpdateProductsPage();
		bool b = UpdatePeriodicProductsPage();
		return a && b;
	}

	bool a = UpdateProductsPage(qvariant_cast<List>(data));
	bool b = UpdatePeriodicProductsPage(qvariant_cast<List>(data));
	return a && b;
}

bool ProductPagesController::UpdateViewProductSubPage(PageData data)
{
	if (!data.canConvert<Product>())
	{
		return true; // skip update for this case if PageData is invalid
	}
	return UpdateViewPage(qvariant_cast<Product>(data));
}

bool ProductPagesController::UpdateViewPeriodicProductSubPage(PageData data)
{
	if (!data.canConvert<PeriodicProduct>())
	{
		return true; // skip update for this case if PageData is invalid
	}
	return UpdateViewPage(qvariant_cast<PeriodicProduct>(data));
}


void ProductPagesController::ConnectProductsPage()
{
	connect(
		&m_products_page,
		&ProductsSubPage::ProductClicked,
		this,
		&ProductPagesController::OnProductClicked);

	connect(
		&m_products_page,
		&ProductsSubPage::PeriodicProductClicked,
		this,
		&ProductPagesController::OnPeriodicProductClicked);

	connect(
		&m_products_page,
		&ProductsSubPage::GoToCreateProduct,
		this,
		&ProductPagesController::OnGoToCreateProduct);

	connect(
		&m_products_page,
		&ProductsSubPage::GoToCreatePeriodicProduct,
		this,
		&ProductPagesController::OnGoToCreatePeriodicProduct);
}


void ProductPagesController::ConnectViewPage()
{
	connect(
		&m_view_page,
		&ProductViewSubPage::EditProduct,
		this,
		&ProductPagesController::OnEditProduct);

	connect(
		&m_view_page,
		&ProductViewSubPage::DeleteProduct,
		this,
		&ProductPagesController::OnDeleteProduct);
}

void ProductPagesController::ConnectPeriodicViewPage()
{
	connect(
		&m_periodic_view_page,
		&PeriodicProductViewSubPage::EditProduct,
		this,
		&ProductPagesController::OnEditPeriodicProduct);

	connect(
		&m_periodic_view_page,
		&PeriodicProductViewSubPage::DeleteProduct,
		this,
		&ProductPagesController::OnDeletePeriodicProduct);
}

void ProductPagesController::ConnectEditPage()
{
	connect(
		&m_edit_page,
		&ProductEditSubPage::UpdateProduct,
		this,
		&ProductPagesController::OnUpdateProduct);
	connect(
		&m_edit_page,
		&ProductEditSubPage::UpdateCategories,
		this,
		&ProductPagesController::UpdateCategoryBox);
}

void ProductPagesController::ConnectPeriodicEditPage()
{
	connect(
		&m_periodic_edit_page,
		&PeriodicProductEditSubPage::CreateProduct,
		this,
		&ProductPagesController::OnUpdatePeriodicProduct);
	connect(
		&m_periodic_edit_page,
		&PeriodicProductEditSubPage::UpdateCategories,
		this,
		&ProductPagesController::UpdateCategoryBox);
}


void ProductPagesController::ConnectCreatePage()
{
	connect(
		&m_create_page,
		&ProductCreateSubPage::CreateProduct,
		this,
		&ProductPagesController::OnCreateProduct);
	connect(
		&m_create_page,
		&ProductCreateSubPage::UpdateCategories,
		this,
		&ProductPagesController::UpdateCategoryBox);
}

void ProductPagesController::ConnectPeriodicCreatePage()
{
	connect(
		&m_periodic_create_page,
		&PeriodicProductCreateSubPage::CreateProduct,
		this,
		&ProductPagesController::OnCreatePeriodicProduct);
	connect(
		&m_periodic_create_page,
		&PeriodicProductCreateSubPage::UpdateCategories,
		this,
		&ProductPagesController::UpdateCategoryBox);
}

void ProductPagesController::OnProductClicked(const Product& product)
{
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PRODUCT, data);
}


void ProductPagesController::OnPeriodicProductClicked(const PeriodicProduct& product)
{
	PageData data{};
	data.setValue(product);
	emit ChangeSubPage(MainSubPages::VIEW_PERIODIC_PRODUCT, data);
}

void ProductPagesController::OnEditProduct()
{
	m_edit_page.set_product(m_view_page.get_product());
	m_edit_page.Update();
	UpdateCategoryBox();
	emit ChangeSubPage(MainSubPages::EDIT_PRODUCT);
}

void ProductPagesController::OnEditPeriodicProduct()
{
	m_periodic_edit_page.set_product(m_periodic_edit_page.get_product());
	m_edit_page.Update();
	UpdateCategoryBox();
	emit ChangeSubPage(MainSubPages::EDIT_PRODUCT);
}

void ProductPagesController::OnUpdateProduct()
{
	UpdateProductModel model{m_hostname};

	Product product = m_edit_page.get_product();

	if (!m_view_page.get_product().is_bought && product.is_bought)
	{
		QDateTime date = QDateTime::currentDateTime();
		product.purchase_date = date.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	}

	if (m_view_page.get_product().is_bought && !product.is_bought)
	{
		QDateTime date = QDateTime::currentDateTime();
		product.purchase_date = date.toString("");
	}

	auto request = model.FormRequest(product);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return;
	}

	emit GoBack(2);
}

void ProductPagesController::OnUpdatePeriodicProduct()
{
	UpdatePeriodicProductModel model{m_hostname};

	PeriodicProduct product;

	product = m_periodic_edit_page.get_product();

	auto request = model.FormRequest(product);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return;
	}

	emit GoBack(2);
}

void ProductPagesController::OnGoToCreateProduct(IdType list_id)
{
	m_list_id = list_id;
	m_create_page.Clear();
	emit ChangeSubPage(MainSubPages::CREATE_PRODUCT);
}

void ProductPagesController::OnGoToCreatePeriodicProduct(IdType list_id)
{
	m_list_id = list_id;
	m_periodic_create_page.Clear();
	emit ChangeSubPage(MainSubPages::CREATE_PERIODIC_PRODUCT);
}

void ProductPagesController::OnCreateProduct()
{
	AddProductModel model{m_hostname};

	Product new_product;
	new_product.id = 0;
	new_product.name = m_create_page.GetName();
	new_product.price = m_create_page.GetPrice();
	new_product.amount = m_create_page.GetAmount();
	new_product.priority = m_create_page.GetPriority();
	new_product.is_bought = m_create_page.GetIsBought();
	new_product.category.id = m_create_page.GetCategoryId();
	new_product.category.name = m_create_page.GetCategoryName();
	new_product.buy_until_date = m_create_page.GetBuyUntil();
	QDateTime date = QDateTime::currentDateTime();
	new_product.add_date = date.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);

	if (m_create_page.GetIsBought())
	{
		QDateTime date = QDateTime::currentDateTime();
		new_product.purchase_date =  date.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	}

	new_product.list_id = m_list_id;

	auto request  = model.FormRequest(new_product);
	//todo catch poco exception
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return ;
	}

	auto product_id = model.ParseResponse(response);
	Q_UNUSED(product_id);

	emit GoBack();
}

void ProductPagesController::OnCreatePeriodicProduct()
{
	AddPeriodicProductModel model{m_hostname};

	PeriodicProduct new_product;
	new_product.id = 0;
	new_product.name = m_periodic_create_page.GetName();
	new_product.price = m_periodic_create_page.GetPrice();
	new_product.amount = m_periodic_create_page.GetAmount();
	new_product.priority = m_periodic_create_page.GetPriority();
	new_product.category.id = m_periodic_create_page.GetCategoryId();
	new_product.category.name = m_periodic_create_page.GetCategoryName();
	new_product.add_until = m_periodic_create_page.GetGenerateUntil();

	new_product.list_id = m_list_id;

	auto request  = model.FormRequest(new_product);
	//todo catch poco exception
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return ;
	}

	auto product_id = model.ParseResponse(response);
	Q_UNUSED(product_id);

	emit GoBack();
}

void ProductPagesController::OnDeleteProduct()
{
	RemoveProductModel model{m_hostname};
	ProductId id{m_view_page.get_product().id};
	auto request = model.FormRequest(id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return;
	}

	emit GoBack();
}

void ProductPagesController::OnDeletePeriodicProduct()
{
	RemovePeriodicProductModel model{m_hostname};
	PeriodicProductId id{m_periodic_view_page.get_product().id};
	auto request = model.FormRequest(id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return;
	}

	emit GoBack();
}

bool ProductPagesController::UpdateProductsPage()
{
	GetProductsModel model{m_hostname};
	List list = m_products_page.get_regular_list();
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto products = model.ParseResponse(response);

	m_products_page.Update(products);
	return true;
}

bool ProductPagesController::UpdatePeriodicProductsPage()
{
	GetPeriodicProductsModel model{m_hostname};
	List list = m_products_page.get_periodic_list();
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto products = model.ParseResponse(response);

	m_products_page.Update(products);
	return true;
}

bool ProductPagesController::UpdateProductsPage(List list)
{
	GetProductsModel model{m_hostname};

	m_products_page.set_regular_list(list);
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto products = model.ParseResponse(response);
	UpdateCategoryBox();
	SetRangeOfSpinBoxes();
	m_products_page.Update(products);
	return true;
}

bool ProductPagesController::UpdatePeriodicProductsPage(List list)
{
	GetPeriodicProductsModel model{m_hostname};

	m_products_page.set_periodic_list(list);
	auto request  = model.FormRequest(list.id);
	auto response = m_http_client.Request(request);

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto products = model.ParseResponse(response);
	UpdateCategoryBox();
	SetRangeOfSpinBoxes();
	m_products_page.Update(products);
	return true;
}


bool ProductPagesController::UpdateViewPage(Product product)
{
	m_view_page.set_product(product);
	m_view_page.Update();
	return true;
}

bool ProductPagesController::UpdateViewPage(PeriodicProduct product)
{
	m_periodic_view_page.set_product(product);
	m_periodic_view_page.Update();
	return true;
}

void ProductPagesController::UpdateProductColors()
{
	m_products_page.UpdateColors();
}


void ProductPagesController::UpdateCategoryBox()
{
	GetProductCategoriesModel model{m_hostname};
	auto request = model.FormRequest(m_user_id);

	try
	{
		auto response = m_http_client.Request(request);

		if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
		{
			emit ServerError(response.status, response.reason);
			return ;
		}

		m_edit_page.FillCategoryBox(model.ParseResponse(response));
		m_create_page.FillCategoryBox(model.ParseResponse(response));
	}
	catch (const Poco::Exception& ex)
	{
		return;
	}
}

void ProductPagesController::SetRangeOfSpinBoxes()
{
	m_edit_page.SetRangeOfSpinBox();
	m_create_page.SetRangeOfSpinBox();
}
