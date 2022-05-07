#pragma once

#include <QWidget>

namespace Ui {
class SettingsSubPage;
}

class SettingsSubPage : public QWidget
{
	Q_OBJECT

public:
	explicit SettingsSubPage(QWidget *parent = nullptr);
	~SettingsSubPage();

	void GoToMainSubPage();
	void SetEmail(const QString& email);

private:
	Ui::SettingsSubPage *m_ui;

	void EraseLineEdits();

private slots:
	void OnChangePasswordButtonClicked();
	void OnChangeEmailButtonClicked();
	void OnSubmitPasswordChangeButtonClicked();
	void OnSubmitEmailChangeButtonClicked();
	void OnGoBackClicked();

signals:
	void ChangeEmail(const QString& old_email, const QString& new_email);
};

