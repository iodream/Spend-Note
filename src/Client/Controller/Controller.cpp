#include "Controller.h"

Controller::Controller()
{
	QObject::connect(
		this, SIGNAL(SetCurrentPage(UIPages)),
		&main_window, SLOT(OnCurrentPageChange(UIPages)));
}

void Controller::Start()
{
	main_window.show();
	emit SetCurrentPage(UIPages::LOGIN);
}

//void Controller::OnLogin(LoginInDTO loginInDTO)
//{
//	LoginModel loginModel;

//    // LoginOutDTO loginOutDTO = httpClient.Request();

//    LoginOutDTO loginOutDTO;
//    loginOutDTO.status = "fail";
//    loginOutDTO.reason = "login or password mismatch";

//    if(loginOutDTO.status == "ok")
//    {
//        emit this->OnSuccessLogin(UIPages::AUTHORIZED);
//    }
//    else if(loginOutDTO.status == "fail")
//    {
//        emit this->OnUnsuccessLogin(loginOutDTO.reason);
//    }
//};

