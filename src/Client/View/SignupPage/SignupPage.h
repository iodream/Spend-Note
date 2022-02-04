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

signals:
	void Signup(const SignupModel::SignupInDTO& dto);
	void GotoLoginPage();

private slots:
	void OnSignupSubmitButtonClicked();
	void OnGoBackButtonClicked();

private:
	Ui::SignupPage *m_ui;
};
