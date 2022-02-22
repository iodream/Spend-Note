#include "IncomePagesController.h"

#include "Models/Income/GetIncomesModel.h"
#include "Models/Income/GetIncomeCategoriesModel.h"

#include "Net/Constants.h"

IncomePagesController::IncomePagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	IncomeListSubPage& incomes_page,
	IncomeViewSubPage& income_view_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_incomes_page{incomes_page}
	, m_income_view_page{income_view_page}
{
	ConnectIncomesPage();
	ConnectIncomeViewPage();
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
}

void IncomePagesController::ConnectIncomeViewPage()
{
	connect(
		&m_income_view_page,
		&IncomeViewSubPage::GoToEditIncome,
		this,
		&IncomePagesController::OnGoToEditIncome);

	connect(
		&m_income_view_page,
		&IncomeViewSubPage::DeleteIncome,
		this,
		&IncomePagesController::OnGoToDeleteIncome);
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

bool IncomePagesController::UpdateIncomeViewPage(const PageData& data)
{
	if (!data.canConvert<Income>()) {
		return false;
	}

	auto income = qvariant_cast<Income>(data);
	m_income_view_page.Update(income);
	return true;
}

void IncomePagesController::OnGoToCreateIncome()
{
	//emit ChangeSubPage(MainSubPages::CREATE_INCOME);
}

void IncomePagesController::OnGoToViewIncome(const Income& income)
{
	PageData data{};
	data.setValue(income);
	emit ChangeSubPage(MainSubPages::VIEW_INCOME, data);
}

bool IncomePagesController::already_added = false;

void IncomePagesController::UpdateCategoryBoxes()
{
	if(!already_added)
	{
		GetIncomeCategoriesModel model(m_hostname);
		auto request = model.FormRequest();

		try
		{
			auto response = m_http_client.Request(request);

			if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
			{
				emit Message(
					QString("Error occured"),
					QString::fromStdString(response.reason));
				return ;
			}

			//m_edit_page.FillCategoryBox(model.ParseResponse(response));
			//m_create_page.FillCategoryBox(model.ParseResponse(response));

			already_added = true;
			}
		catch (const Poco::Exception& ex)
		{
			return;
		}
	}
}

void IncomePagesController::OnGoToEditIncome(const Income& income)
{

}

void IncomePagesController::OnGoToDeleteIncome(const Income& income)
{

}
