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

private:
	Ui::SettingsSubPage *m_ui;

signals:
	void Logout();

private slots:
	void OnLogoutButtonClicked();
};
