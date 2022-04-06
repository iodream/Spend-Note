#include "StatisticsPageController.h"

#include "Models/Categories/Product/GetProductCategoriesModel.h"
#include "Models/Statistics/GetStatisticsPercentagePerCategoryModel.h"
#include "Models/Statistics/GetStatisticsPerCategoryModel.h"
#include "Models/Statistics/GetStatisticsPerDayModel.h"

StatisticsPageController::StatisticsPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	StatisticSubPage& statistics_page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_statistics_page{statistics_page}
{
	ConnectStatisticsPage();
}

bool StatisticsPageController::UpdateStatisticsPage()
{
	m_statistics_page.UpdateCurrentChart();
	return true;
}

std::vector<ProductCategory> StatisticsPageController::GetProductCategories()
{
	GetProductCategoriesModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id);

	Net::Response response;
	try{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		emit ClientError("Request to server failed");
		return {};
	}
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return {};
	}

	return model.ParseResponse(response);
}

void StatisticsPageController::ConnectStatisticsPage()
{
	connect(
		&m_statistics_page,
		&StatisticSubPage::PercentProductChartSelected,
		this,
		&StatisticsPageController::OnPercentChartSelected);

	connect(
		&m_statistics_page,
		&StatisticSubPage::AmountProductChartSelected,
		this,
		&StatisticsPageController::OnAmountChartSelected);

	connect(
		&m_statistics_page,
		&StatisticSubPage::BalanceChartSelected,
		this,
		&StatisticsPageController::OnBalanceChartSelected);
}

void StatisticsPageController::OnPercentChartSelected()
{
	GetStatisticsPercentagePerCategoryModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id, "incomes", "weekly");

	Net::Response response;
	try{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		emit ClientError("Request to server failed");
	}
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
	}

	auto expenses = model.ParseResponse(response);
	auto categories = GetProductCategories();

	m_statistics_page.UpdateProductPiePercentChart(expenses, categories);
}

void StatisticsPageController::OnAmountChartSelected()
{
	GetStatisticsPerCategoryModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id, "incomes", "weekly");

	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		emit ClientError("Request to server failed");
	}
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
	}

	auto expenses = model.ParseResponse(response);
	auto categories = GetProductCategories();

	m_statistics_page.UpdateProductPieAmountChart(expenses, categories);
}

void StatisticsPageController::OnBalanceChartSelected()
{
	GetStatisticsPerDayModel model{m_hostname};
	auto request  = model.FormRequest(m_user_id, "incomes", "weekly");

	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		emit ClientError("Request to server failed");
	}
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
	}

	auto expenses = model.ParseResponse(response);

	m_statistics_page.UpdateBarBalanceChart(expenses);
}
