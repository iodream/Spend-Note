#pragma once

#include <QWidget>

#include "Models/LoginModel.h"
#include "View/Constants.h"

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
	void changeEvent(QEvent* event);
	void Update();


private:
	Ui::LoginPage *m_ui;

signals:
	void GotoSignup();
	void Login(LoginModel::JSONFormatter::Credentials credentials);
	void LanguageChanged();


private slots:
	void OnLoginSubmitButtonClicked();
	void OnSignupButtonClicked();
	void OnPasswordTextChanged(const QString& arg1);
	void OnLoginTextChanged(const QString& arg1);
	void OnLangSelected(QString lang);
	void OnShowPasswordChecked();
};

