#pragma once

#include <QWidget>
#include "Models/SignupModel.h"
#include "View/Constants.h"

namespace Ui {
class SignupPage;
}

class SignupPage : public QWidget
{
	Q_OBJECT

public:
	explicit SignupPage(QWidget *parent = nullptr);
	~SignupPage();

	void SetErrorBanner(const int code, const std::string& description);
	void CloseErrorBanner();

signals:
	void Signup(const SignupModel::SignupInDTO& dto);
	void GoToLoginPage();

private slots:
	void OnSignupSubmitButtonClicked();

private:
	Ui::SignupPage *m_ui;
};
