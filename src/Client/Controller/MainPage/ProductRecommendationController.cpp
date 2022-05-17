#include "ProductRecommendationController.h"

#include "Models/Product/GetRecommendationProductModel.h"
#include "Net/Constants.h"

ProductRecommendationController::ProductRecommendationController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	MainPage& main_page):
	m_http_client(http_client),
	m_hostname(hostname),
	m_user_id(user_id),
	m_main_page(main_page)
{

}

bool ProductRecommendationController::UpdateRecommendations()
{
	GetRecommendationProductModel model{m_hostname};
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
	if(response.status == Poco::Net::HTTPResponse::HTTP_NO_CONTENT)
	{

		emit RecommendationClosed();
		return true;
	}

	auto recommendation = model.ParseResponse(response);
	m_main_page.UpdateRecommendation(recommendation);

	return true;
}
