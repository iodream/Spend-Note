#pragma once

#include <QWidget>

#include "Models/LoginModel.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
	Q_OBJECT

public:
	explicit LoginPage(QWidget *parent = nullptr);
	~LoginPage();

	void ChangeLoginErrorLabel(std::string reason);

	void SetErrorBanner(const int code, const std::string& description);
	void SetErrorBanner(const std::string& description);
	void CloseErrorBanner();

private:
	Ui::LoginPage *m_ui;

signals:
	void GotoSignup();
	void Login(LoginModel::JSONFormatter::Credentials credentials);

private slots:
	void OnLoginSubmitButtonClicked();
	void OnSignupButtonClicked();
	void OnPasswordTextChanged(const QString& arg1);
	void OnLoginTextChanged(const QString& arg1);
	void OnShowPasswordChecked();
};

