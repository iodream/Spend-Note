#pragma once

#include <QInputDialog>
#include <QMessageBox>

#include "HTTPClient.h"

#include "View/SignupPage/SignupPage.h"
#include "Common.h"
#include "View/Constants.h"
#include "Models/SignupModel.h"
#include "Models/AddVerificationModel.h"
#include "Models/CheckVerificationModel.h"

class SignupPageController : public QObject
{
	Q_OBJECT
public:
	SignupPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		SignupPage& page);

	virtual ~SignupPageController() override {};

private:
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;
	SignupPage& m_page;

	void ConnectPage();

	void AddVerification(const std::string& email);
	bool CheckVerification(const std::string& email, const std::string& code);

signals:
	void ChangePage(UIPages page);

public slots:
	void OnSignup(const SignupModel::SignupInDTO& in_dto);
	void OnGoToLoginPage();
};
