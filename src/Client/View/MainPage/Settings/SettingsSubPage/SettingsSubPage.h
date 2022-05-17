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
	void SetEmail(const QString& email);
	void changeEvent(QEvent* event);
	void Update();
	void UpdateColors();
	void FontSizeChange(int);
private:
	Ui::SettingsSubPage *m_ui;
	static int CurColorElemSelected;
	void EraseLineEdits();

signals:
	void FontChange();
	void ChangeEmail(const QString& old_email, const QString& new_email);
	void ColorSchemeChanged();
	void LanguageChanged();

private slots:
	void OnChangePasswordButtonClicked();
	void OnChangeEmailButtonClicked();
	void OnSubmitPasswordChangeButtonClicked();
	void OnSubmitEmailChangeButtonClicked();
	void OnGoBackClicked();
	void OnFontChange();
	void OnColorScheme1Selected();
	void OnColorScheme2Selected();
	void OnColorScheme3Selected();
	void OnColorSchemeCustomSelect(int);
	void OnNewColorSelected();
	void OnLangSelected(QString lang);
	void OnDefaultFontClicked();

};

