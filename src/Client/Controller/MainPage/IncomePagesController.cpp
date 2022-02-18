#include "IncomePagesController.h"

#include "Models/Income/GetIncomesModel.h"
#include "Models/Income/AddIncomeModel.h"


#include "Net/Constants.h"

IncomePagesController::IncomePagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	IncomeListSubPage& incomes_page,
	IncomeCreateSubPage& income_create_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_incomes_page{incomes_page}
	, m_income_create_page{income_create_page}
{
	ConnectIncomesPage();
}

void IncomePagesController::ConnectIncomesPage()
{
	connect(
		&m_incomes_page,
		&IncomeListSubPage::GoToCreateIncome,
		this,
		&IncomePagesController::OnGoToCreateIncome);

	connect(
		&m_incomes_page,
		&IncomeListSubPage::GoToIncomeView,
		this,
		&IncomePagesController::OnGoToViewIncome);

	connect(
		&m_income_create_page,
		&IncomeCreateSubPage::CreateIncome,
		this,
		&IncomePagesController::OnCreateIncome);
}

bool IncomePagesController::UpdateIncomesPage()
{
	GetIncomesModel model{m_hostname};
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
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return false;
	}

	auto incomes = model.ParseResponse(response);
	m_incomes_page.Update(incomes);

	return true;
}

void IncomePagesController::OnGoToCreateIncome()
{
	emit ChangeSubPage(MainSubPages::CREATE_INCOME);
}

void IncomePagesController::OnGoToViewIncome(const Income& income)
{
	PageData data{};
	data.setValue(income);
	emit ChangeSubPage(MainSubPages::VIEW_INCOME, data);
}

void IncomePagesController::OnCreateIncome(Income& income)
{
	AddIncomeModel model{m_hostname};
	income.id = m_user_id;
	auto request  = model.FormRequest(income);

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
		emit Message(
			QString("Error occured"),
			QString::fromStdString(response.reason));
		return;
	}

	//auto incomes = model.ParseResponse(response);
	//m_incomes_page.Update(incomes);
}
