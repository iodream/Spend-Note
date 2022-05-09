#include "SettingsPageController.h"

SettingsPageController::SettingsPageController(
	HTTPClient& http_client,
	std::string& hostname,
	IdType& user_id,
	SettingsSubPage& settings_page)
	: m_http_client(http_client)
	, m_hostname(hostname)
	, m_user_id(user_id)
	, m_settings_page(settings_page)
{
	connect(
		&m_settings_page,
		&SettingsSubPage::FontChange,
		this,
		&SettingsPageController::FontChange);

	connect(
		&m_settings_page,
		&SettingsSubPage::ColorSchemeChanged,
		this,
		&SettingsPageController::OnColorSchemeChanged);

	connect(
		&m_settings_page,
		&SettingsSubPage::LanguageChanged,
		this,
		&SettingsPageController::OnColorSchemeChanged);

	connect(
		&m_settings_page,
		&SettingsSubPage::LanguageChanged,
		this,
		&SettingsPageController::LanguageChanged);
}

void SettingsPageController::OnColorSchemeChanged()
{
	emit ColorSchemeChanged();
}

void SettingsPageController::UpdateSettingsPageColors()
{
	m_settings_page.UpdateColors();
}

void SettingsPageController::UpdateSettingsSubPage()
{
	m_settings_page.Update();
	m_settings_page.GoToMainSubPage();
}
