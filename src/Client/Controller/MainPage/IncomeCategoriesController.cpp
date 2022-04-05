#include "IncomeCategoriesController.h"

#include "Models/Income/GetIncomesModel.h"
#include "Models/Income/AddIncomeModel.h"
#include "Models/Income/RemoveIncomeModel.h"
#include "Models/Income/UpdateIncomeModel.h"
#include "Models/Income/GetIncomeCategoriesModel.h"


#include "Net/Constants.h"

IncomeCategoriesController::IncomeCategoriesController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		CategoryEditPage& category_edit_spage):
		m_http_client(http_client),
		m_hostname(hostname),
		m_user_id(user_id),
		m_category_edit_spage(category_edit_spage)
{
}

bool IncomeCategoriesController::UpdateIncomesCategoryPage()
{
//	GetIncomesModel model{m_hostname};
//	auto request  = model.FormRequest(m_user_id);

//	Net::Response response;
//	try{
//		response = m_http_client.Request(request);
//	}
//	catch(Poco::Exception& exc)
//	{
//		return false;
//	}
//	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
//	{
//		emit ServerError(response.status, response.reason);
//		return false;
//	}

//	auto incomes = model.ParseResponse(response);
//	m_incomes_page.Update(incomes);

	return true;
}



void IncomeCategoriesController::OnAddIncomeCategory()
{
//	AddIncomeModel model{m_hostname};
//	income.id = m_user_id;

//	if(!model.CheckFields(income))
//	{
//		emit ClientError("Fields can't be empty!");
//		return;
//	}

//	if(!model.CheckExpDate(income))
//	{
//		emit ClientError("Expiration date can't be in the past");
//		return;
//	}

//	auto request  = model.FormRequest(income);

//	Net::Response response;
//	try{
//		response = m_http_client.Request(request);
//	}
//	catch(Poco::Exception& exc)
//	{
//		return;
//	}
//	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
//	{
//		emit ServerError(response.status, response.reason);
//		return;
//	}

//	m_income_create_page.Clear();
//	emit GoBack();
}


void IncomeCategoriesController::OnDeleteIncomeCategory()
{
//	RemoveIncomeModel model{m_hostname};
//	IncomeId delete_id;
//	delete_id.id = income.id;

//	auto request = model.FormRequest(delete_id);
//	Net::Response response;
//	try{
//		response = m_http_client.Request(request);
//	}
//	catch(Poco::Exception& exc)
//	{
//		return;
//	}
//	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
//	{
//		emit ServerError(response.status, response.reason);
//		return;
//	}
//	emit GoBack();
}

void IncomeCategoriesController::OnUpdateIncomeCategory()
{
//	UpdateIncomeModel model{m_hostname};

//	const Income& income = m_income_edit_page.get_income();

//	if(!model.CheckFields(income))
//	{
//		emit ClientError("Fields can't be empty!");
//		return;
//	}

//	if(model.CheckExpDate(income))
//	{
//		emit ClientError("Expiration date can't be in the past");
//		return;
//	}

//	auto request  = model.FormRequest(income);

//	Net::Response response;
//	try{
//		response = m_http_client.Request(request);
//	}
//	catch(Poco::Exception& exc)
//	{
//		return;
//	}
//	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
//	{
//		emit ServerError(response.status, response.reason);
//		return;
//	}
//	emit GoBack(2);
}
