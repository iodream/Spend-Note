#pragma once

#include "HTTPClient.h"

#include "View/LoginPage/LoginPage.h"
#include "Common.h"
#include "View/Constants.h"
#include "Models/LoginModel.h"

class LoginPageController : public QObject
{
	Q_OBJECT
public:
	LoginPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		LoginPage& page);

	virtual ~LoginPageController() override {};

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;
	LoginPage& m_page;
	void ConnectPage();

signals:
	void Message(const QString& window_name, const QString& message);
	void ChangePage(UIPages page);

public slots:
	void OnLogin(LoginModel::JSONFormatter::Credentials credentials);
	void OnGoToSignupPage();
};
