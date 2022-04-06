#include "IncomePagesController.h"

#include "Models/Income/GetIncomesModel.h"
#include "Models/Income/AddIncomeModel.h"
#include "Models/Income/RemoveIncomeModel.h"
#include "Models/Income/UpdateIncomeModel.h"
#include "Models/Categories/Income/GetIncomeCategoriesModel.h"


#include "Net/Constants.h"

IncomePagesController::IncomePagesController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	IncomeListSubPage& incomes_page,
	IncomeCreateSubPage& income_create_page,
	IncomeViewSubPage& income_view_page,
	IncomeEditSubPage& income_edit_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_incomes_page{incomes_page}
	, m_income_create_page{income_create_page}
	, m_income_view_page{income_view_page}
	, m_income_edit_page{income_edit_page}

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

	connect(
		&m_income_create_page,
		&IncomeCreateSubPage::CreateIncome,
		this,
		&IncomePagesController::OnCreateIncome);
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
		&IncomePagesController::OnDeleteIncome);

	connect(
		&m_income_edit_page,
		&IncomeEditSubPage::UpdateIncome,
		this,
		&IncomePagesController::OnUpdateIncome);

	connect(
		&m_income_create_page,
		&IncomeCreateSubPage::UpdateCategories,
		this,
		&IncomePagesController::UpdateCategoryBoxes);
	connect(
		&m_income_edit_page,
		&IncomeEditSubPage::UpdateCategories,
		this,
		&IncomePagesController::UpdateCategoryBoxes);
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
		emit ServerError(response.status, response.reason);
		return false;
	}

	auto incomes = model.ParseResponse(response);
	m_incomes_page.Update(incomes);

	return true;
}

bool IncomePagesController::UpdateIncomeViewPage(const PageData& data)
{
	if (!data.canConvert<Income>()) {
		return true; // skip update for this case if PageData is invalid
	}

	auto income = qvariant_cast<Income>(data);
	m_income_view_page.Update(income);
	return true;
}


bool IncomePagesController::UpdateIncomeEditPage(const PageData& data)
{
	UpdateCategoryBoxes();
	if (!data.canConvert<Income>()) {
		return false;
	}

	auto income = qvariant_cast<Income>(data);
	m_income_edit_page.Update(income);
	return true;
}

void IncomePagesController::OnGoToCreateIncome()
{
	UpdateCategoryBoxes();
	m_income_create_page.SetMinimumDate(QDate::currentDate());
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

	QDateTime date(QDate::fromString(income.expiration_time), QTime(0,0));
	income.expiration_time = date.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);
	date = QDateTime(QDate::fromString(income.add_time), QTime(0,0));
	income.add_time = date.toString(DATE_FORMAT_YYYY_MM_DD_HH_MM_SS);

	if(!model.CheckFields(income))
	{
		emit ClientError("Fields can't be empty!");
		return;
	}

	if(!model.CheckExpDate(income))
	{
		emit ClientError("Expiration date can't be in the past");
		return;
	}

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
		emit ServerError(response.status, response.reason);
		return;
	}

	m_income_create_page.Clear();
	emit GoBack();
}

void IncomePagesController::UpdateCategoryBoxes()
{
		GetIncomeCategoriesModel model{m_hostname};
		auto request = model.FormRequest(m_user_id);

		try
		{
			auto response = m_http_client.Request(request);

			if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
			{
				emit ServerError(response.status, response.reason);
				return ;
			}

			m_income_edit_page.FillCategoryBox(model.ParseResponse(response));
			m_income_create_page.FillCategoryBox(model.ParseResponse(response));
		}
		catch (const Poco::Exception& ex)
		{
			return;
		}
}

void IncomePagesController::OnGoToEditIncome(const Income& income)
{
	PageData data{};
	data.setValue(income);
	m_income_edit_page.SetMinimumDate(QDate::currentDate());
	emit ChangeSubPage(MainSubPages::EDIT_INCOME, data);
}

void IncomePagesController::OnDeleteIncome(const Income& income)
{
	RemoveIncomeModel model{m_hostname};
	IncomeId delete_id;
	delete_id.id = income.id;

	auto request = model.FormRequest(delete_id);
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
	emit GoBack();
}

void IncomePagesController::OnUpdateIncome()
{
	UpdateIncomeModel model{m_hostname};

	const Income& income = m_income_edit_page.get_income();

	if(!model.CheckFields(income))
	{
		emit ClientError("Fields can't be empty!");
		return;
	}

	if(model.CheckExpDate(income))
	{
		emit ClientError("Expiration date can't be in the past");
		return;
	}

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
		emit ServerError(response.status, response.reason);
		return;
	}
	emit GoBack(2);
}
