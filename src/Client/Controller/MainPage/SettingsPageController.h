#pragma once

#include <QObject>

#include "Controller/HTTPClient.h"

#include "View/MainPage/Settings/SettingsSubPage/SettingsSubPage.h"
//#include "Models/List/GetDailyListModel.h"

#include "View/Constants.h"
#include "Entities/PageData.h"

class SettingsPageController : public QObject
{
	Q_OBJECT
public:
	explicit SettingsPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		SettingsSubPage& settings_page);

	virtual ~SettingsPageController() override {}

	void UpdateSettingsSubPage();

private:
	SettingsSubPage& m_settings_page;
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});
	void ColorSchemeChanged();
	void GoBack(int n=1);

public slots:
	void OnColorSchemeChanged();
};

