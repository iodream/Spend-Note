#pragma once

#include <QWidget>
#include "View/Constants.h"

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
	void changeEvent(QEvent* event);
	void Update();


	void UpdateColors();
private:
	Ui::SettingsSubPage *m_ui;
	static int CurColorElemSelected;
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
	void OnNewColorSelected();
	void OnLangSelected(QString lang);

signals:
	void ColorSchemeChanged();
	void LanguageChanged();


};

