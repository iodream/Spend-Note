#include "Controller.h"

void Controller::OnLogin(LoginInDTO loginInDTO)
{
    LoginModel loginModel;
    loginModel.RequestDTO(loginInDTO);

    // LoginOutDTO loginOutDTO = httpClient.Request();

    LoginOutDTO loginOutDTO;
    loginOutDTO.status = "fail";
    loginOutDTO.reason = "login and password`s mismatch";

    if(loginOutDTO.status == "ok")
    {
        emit this->OnSuccessLogin(UIPages::AUTHORIZED);
    }
    else if(loginOutDTO.status == "fail")
    {
        emit this->OnUnsuccessLogin(loginOutDTO.reason);
    }
};

