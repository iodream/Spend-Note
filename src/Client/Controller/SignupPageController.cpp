#include "SignupPageController.h"

#include "Models/LoginModel.h"

#include "Net/Constants.h"

SignupPageController::SignupPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	SignupPage& page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_page{page}
{
	ConnectPage();
}

void SignupPageController::ConnectPage()
{
	connect(
		&m_page,
		&SignupPage::Signup,
		this,
		&SignupPageController::OnSignup);

	connect(
		&m_page,
		&SignupPage::GoToLoginPage,
		this,
		&SignupPageController::OnGoToLoginPage);
}

void SignupPageController::OnSignup(const SignupModel::SignupInDTO& in_dto)
{
	SignupModel model{m_hostname};
	if (!model.CheckPassRepeat(in_dto))
	{
		m_page.SetErrorBanner("Passwords must match!");
		return;
	}

	if (!model.CheckData(in_dto))
	{
		m_page.SetErrorBanner("Email or password can't be empty!");
		return;
	}

	auto request  = model.FormRequest(in_dto);
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
		if(response.status == Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CONFLICT)
		{
			m_page.SetErrorBanner(response.status, response.reason);
			return;
		}
	}

	emit ChangePage(UIPages::LOGIN);
}

void SignupPageController::OnGoToLoginPage()
{
	m_page.CloseErrorBanner();
	emit ChangePage(UIPages::LOGIN);
}
