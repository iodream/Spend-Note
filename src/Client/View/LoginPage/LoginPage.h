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
	void Login(LoginModel::JSONFormatter::LoginInDTO);

private slots:
	void OnLoginSubmitButtonClicked();
};

