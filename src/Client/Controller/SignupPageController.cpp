#include "SignupPageController.h"

#include "Models/LoginModel.h"
#include "Net/Constants.h"

#include <chrono>
#include <thread>




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
	QObject::connect(
		&m_page,
		&SignupPage::Signup,
		this,
		&SignupPageController::OnSignup);

	QObject::connect(
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
		emit Message(
			QString("Error"),
			QString("Passwords must match!"));
		return;
	}

	if (!model.CheckData(in_dto))
	{
		emit Message(
			QString("Error"),
			QString("Username or password can't be empty!"));
		return;
	}

	auto request  = model.FormRequest(in_dto);

	Net::Response response;

	int Retries = 0;
	retry:
		try{
			Retries++;
			response = m_http_client.Request(request);
		}
		catch(Poco::Exception& exc)
		{
			if(Retries < Net::CONN_RETRY_MAX)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				goto retry;
			}
			emit Message(
					QString("Connection failed!"),
					QString("Connection failed after %1 retries").arg(Retries));
			return;
		}


	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		if(response.status == Poco::Net::HTTPServerResponse::HTTPStatus::HTTP_CONFLICT)
		{
			emit Message(
				QString("Error"),
				QString("User already exists!"));
			return;
		}
	}

	emit ChangePage(UIPages::LOGIN);
}

void SignupPageController::OnGoToLoginPage()
{
	emit ChangePage(UIPages::LOGIN);
}
