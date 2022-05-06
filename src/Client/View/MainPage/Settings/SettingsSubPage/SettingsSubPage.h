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
	void Update();

	void UpdateColors();
private:
	Ui::SettingsSubPage *m_ui;
	static int CurColorElemSelected;
	void EraseLineEdits();

signals:
	void FontChange();

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
	void OnDefaultFontClicked();
	void FontSizeChange(int);

signals:
	void ColorSchemeChanged();
};

