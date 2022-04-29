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
		[this](QFont font){ emit(FontChange(font)); });
}

void SettingsPageController::UpdateSettingsSubPage()
{
	m_settings_page.GoToMainSubPage();
}
