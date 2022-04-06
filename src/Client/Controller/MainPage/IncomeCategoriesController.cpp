#include "IncomeCategoriesController.h"

#include "Models/Categories/Income/GetIncomeCategoriesModel.h"
#include "Models/Categories/Income/AddIncomeCategoryModel.h"
#include "Models/Categories/Income/UpdateIncomeCategoryModel.h"
#include "Models/Categories/Income/RemoveIncomeCategoryModel.h"


#include "Net/Constants.h"

IncomeCategoriesController::IncomeCategoriesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	CategoryEditPage& category_edit_spage,
	IncomeCreateSubPage& income_create_page,
	IncomeEditSubPage& income_edit_page):
	m_http_client(http_client),
	m_hostname(hostname),
	m_user_id(user_id),
	m_category_edit_spage(category_edit_spage),
	m_income_create_page(income_create_page),
	m_income_edit_page(income_edit_page)
{
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::AddIncomeCategory,
		this,
		&IncomeCategoriesController::OnAddIncomeCategory);
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::RemoveIncomeCategory,
		this,
		&IncomeCategoriesController::OnDeleteIncomeCategory);
	connect(
		&m_category_edit_spage,
		&CategoryEditPage::UpdateIncomeCategory,
		this,
		&IncomeCategoriesController::OnUpdateIncomeCategory);
	connect(
		&m_income_create_page,
		&IncomeCreateSubPage::AddIncomeCategory,
		this,
		&IncomeCategoriesController::OnAddIncomeCategory);
	connect(
		&m_income_edit_page,
		&IncomeEditSubPage::AddIncomeCategory,
		this,
		&IncomeCategoriesController::OnAddIncomeCategory);
}

bool IncomeCategoriesController::UpdateIncomeCategoryPage()
{
	GetIncomeCategoriesModel model{m_hostname};
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



void IncomeCategoriesController::OnAddIncomeCategory(IncomeCategory category)
{
	AddIncomeCategoryModel model{m_hostname};
	category.id = 0;

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
	UpdateIncomeCategoryPage();
}


void IncomeCategoriesController::OnDeleteIncomeCategory(IncomeCategoryId id)
{
	RemoveIncomeCategoryModel model{m_hostname};

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
	UpdateIncomeCategoryPage();
}

void IncomeCategoriesController::OnUpdateIncomeCategory(IncomeCategory category)
{
	UpdateIncomeCategoryModel model{m_hostname};

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
	UpdateIncomeCategoryPage();
}
