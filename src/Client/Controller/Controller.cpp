#include "Controller.h"

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

void Controller::OnLogin(LoginInDTO loginInDTO)
{
    LoginModel loginModel;

    // LoginOutDTO loginOutDTO = httpClient.Request();

    LoginOutDTO loginOutDTO;
}

