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

void LoginPageController::UpdateLoginPage()
{
	m_page.Update();
}

void LoginPageController::ConnectPage()
{
	connect(
		&m_page,
		&LoginPage::Login,
		this,
		&LoginPageController::OnLogin);

	connect(
		&m_page,
		&LoginPage::GotoSignup,
		this,
		&LoginPageController::OnGoToSignupPage);

	connect(
		&m_page,
		&LoginPage::LanguageChanged,
		this,
		&LoginPageController::LanguageChanged);
}

void LoginPageController::AddVerification(const std::string& email)
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

void LoginPageController::CheckVerification(const std::string& email, const std::string& code)
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

void LoginPageController::OnLogin(LoginModel::JSONFormatter::Credentials credentials)
{
	LoginModel model{m_hostname};

	if(!model.IsEmailValid(QString::fromStdString(credentials.email)))
	{
		m_page.SetErrorBanner("Type valid email");
		return;
	}

	auto request  = model.FormRequest(credentials);
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
		if(response.status == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
		{
			if(response.reason == Net::VERIFICATION_FAILED)
			{
				AddVerification(credentials.email); // ask for verification
				bool isOkPressed;

				QMessageBox::information(
					&m_page,
					tr("Spend&Note"),
					tr("Verification code has been sent on ") +
					QString::fromStdString(credentials.email));
				QString code = QInputDialog::getText(
					&m_page,
					tr("Input your verification code"),
					tr("Code: "),
					QLineEdit::Normal,
					"", &isOkPressed); // "" field is empty since we will not use default text for code label

				if(!isOkPressed)
				{
					m_page.SetErrorBanner(
						"Email verification was not passed!");
					return;
				}

				CheckVerification(credentials.email, code.toStdString());
				OnLogin(credentials);
			}
			else
			{
				m_page.ChangeLoginErrorLabel(
					"Login or password is incorrect");
			}
			m_page.ChangeLoginErrorLabel(
				tr("Login or password is incorrect").toStdString());
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

	emit SetEmail(credentials.email);
	emit ReadSettings();
	MainPage::bNeedsGlobalUIUpdate = true;
	emit ChangePage(UIPages::MAIN);
}

void LoginPageController::OnGoToSignupPage()
{
	m_page.CloseErrorBanner();
	emit ChangePage(UIPages::SIGNUP);
}
