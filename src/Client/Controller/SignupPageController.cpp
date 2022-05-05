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

void SignupPageController::AddVerification(const std::string& email)
{
	AddVerificationModel add_verification_model{m_hostname};
	AddVerificationModel::VerificationInDTO add_verification_dto;
	add_verification_dto.email = email;
	Net::Request request = add_verification_model.FormRequest(add_verification_dto);
	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		m_page.SetErrorBanner(response.status, response.reason);
		return;
	}
}

void SignupPageController::CheckVerification(const std::string& email, const std::string& code)
{
	CheckVerificationModel model{m_hostname};
	CheckVerificationModel::VerificationInDTO dto{email, code};

	if(!model.CheckData(dto))
	{
		m_page.SetErrorBanner("\"Code\" field should not be empty!");
		return;
	}

	Net::Request request = model.FormRequest(dto);
	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		m_page.SetErrorBanner(response.status, response.reason);
		return;
	}
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
		m_page.SetErrorBanner("Username or password can't be empty!");
		return;
	}

	if (!model.IsEmailValid(in_dto))
	{
		m_page.SetErrorBanner("Email should be valid!");
		return;
	}

	auto request  = model.FormRequest(in_dto);
	Net::Response response;
	try
	{
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

	AddVerification(in_dto.email); // ask for verification

	QMessageBox::information(
		&m_page,
		tr("Spend&Note"),
		tr("Verification code has been sent on ") + QString::fromStdString(in_dto.email));
	QString code = QInputDialog::getText(
		&m_page,
		tr("Input your verification code"),
		tr("Code: "));

	CheckVerification(in_dto.email, code.toStdString()); // checking verification

	emit ChangePage(UIPages::LOGIN);
}

void SignupPageController::OnGoToLoginPage()
{
	m_page.CloseErrorBanner();
	emit ChangePage(UIPages::LOGIN);
}
