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
};

