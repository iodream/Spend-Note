#include "LoginPageController.h"

#include "Models/LoginModel.h"
#include "View/MainPage/MainPage.h"

#include "Net/Constants.h"


LoginPageController::LoginPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	LoginPage& page)
	: m_http_client{http_client}
	, m_hostname{hostname}
	, m_user_id{user_id}
	, m_page{page}
{
	ConnectPage();
}

void LoginPageController::ConnectPage()
{
	QObject::connect(
		&m_page,
		&LoginPage::Login,
		this,
		&LoginPageController::OnLogin);

	QObject::connect(
		&m_page,
		&LoginPage::GotoSignup,
		this,
		&LoginPageController::OnGoToSignupPage);
}

void LoginPageController::OnLogin(LoginModel::JSONFormatter::Credentials credentials)
{
	LoginModel model{m_hostname};
	auto request  = model.FormRequest(credentials);
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
		if(response.status == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
		{
			m_page.ChangeLoginErrorLabel(
				"Email or password is incorrect");
		}
		else
		{
			m_page.SetErrorBanner(response.status, response.reason);
		}
		return;
	}

	auto user_data = model.ParseResponse(response);

	m_user_id = user_data.id; // setting user id

	m_http_client.set_auth_scheme(Net::AUTH_SCHEME_TYPE_BEARER);
	m_http_client.set_token(user_data.token);

	emit ReadSettings();
	MainPage::bNeedColorUpdate = true;
	emit ChangePage(UIPages::MAIN);
}

void LoginPageController::OnGoToSignupPage()
{
	m_page.CloseErrorBanner();
	emit ChangePage(UIPages::SIGNUP);
}
