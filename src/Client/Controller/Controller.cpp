#include "Controller.h"

Controller::Controller()
{
	QObject::connect(
		this, SIGNAL(SetCurrentPage(UIPages)),
		&main_window, SLOT(OnCurrentPageChange(UIPages)));

    QObject::connect(
                &main_window.loginPage, &LoginPage::Login,
                this, &Controller::OnLogin);
}

void Controller::Start()
{
	main_window.show();
	emit SetCurrentPage(UIPages::LOGIN);
}

void Controller::OnLogin(LoginInDTO loginInDTO)
{
    // zaglushka
    LoginModel loginModel;

    // LoginOutDTO loginOutDTO = httpClient.Request();

    LoginOutDTO loginOutDTO;
    loginOutDTO.status = "ok";
    loginOutDTO.reason = "login or password mismatch";

    if(loginOutDTO.status == "ok")
    {
        emit SetCurrentPage(UIPages::HOME);
    }
    else if(loginOutDTO.status == "fail")
    {
        QMessageBox::critical(&main_window,
                              tr("xi jinping"),
                              tr("your public execution will be tomorrow"));
    }
}

