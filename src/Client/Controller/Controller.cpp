#include "Controller.h"

#include "Net/Constants.h"

Controller::Controller()
{
    QObject::connect(
		&main_window.loginPage, &LoginPage::Login,
		this, &Controller::OnLogin);
}

void Controller::Start()
{
	main_window.show();
	main_window.SetCurrentPage(UIPages::LOGIN);
}

void Controller::OnLogin(LoginInDTO in_dto)
{
	LoginModel model;
	auto request  = model.FormRequest(in_dto);
	auto response = m_http_client.Request(request);

    // checking response status
	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		if(response.status == Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
		{
			main_window.loginPage.ChangeLoginErrorLabel(
					"Login and password do not match");
		}
		else
		{
			QMessageBox::information(&main_window
					, tr("Login failed!")
					, tr(response.reason.c_str()));
		}
		return;
    }

	auto out_dto = model.ParseResponse(response);

	m_http_client.set_auth_scheme(Net::AUTH_SCHEME_TYPE_BEARER);
	m_http_client.set_token(out_dto.token);

	// there i could set new data to the page

    main_window.SetCurrentPage(UIPages::HOME);
}
