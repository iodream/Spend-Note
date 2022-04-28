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

private:
	Ui::SettingsSubPage *m_ui;

	void EraseLineEdits();

private slots:
	void OnChangePasswordButtonClicked();
	void OnChangeEmailButtonClicked();
	void OnSubmitPasswordChangeButtonClicked();
	void OnSubmitEmailChangeButtonClicked();
	void OnGoBackClicked();
	void OnColorScheme1Selected();
	void OnColorScheme2Selected();
	void OnColorScheme3Selected();
	void OnColorSchemeCustomSelect(int);
	void OnCustomColorSchemeSaveAll();
	void OnUseCustomColorScheme();
signals:
	void ColorSchemeChanged();
	void SaveColorConfig();
};

