#pragma once

#include <QWidget>

#include "DTO/Login.h"

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
	void Login(LoginInDTO);
	void GotoSignup();

private slots:
	void OnLoginSubmitButtonClicked();
	void OnSignupButtonClicked();
	void OnPasswordTextChanged(const QString& arg1);
	void OnLoginTextChanged(const QString& arg1);
};

