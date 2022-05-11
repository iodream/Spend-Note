#pragma once

#include <QObject>
#include <QMessageBox>
#include <QInputDialog>

#include "Controller/HTTPClient.h"

#include "View/MainPage/Settings/SettingsSubPage/SettingsSubPage.h"
#include "Models/AddVerificationModel.h"
#include "Models/User/ChangeEmailModel.h"

#include "View/Constants.h"
#include "Entities/PageData.h"
#include "Entities/Entities.h"

class SettingsPageController : public QObject
{
	Q_OBJECT
public:
	explicit SettingsPageController(
		HTTPClient& http_client,
		std::string& hostname,
		IdType& user_id,
		SettingsSubPage& settings_page);

	virtual ~SettingsPageController() override {};

	void UpdateSettingsSubPage();
	void ConnectSettingsPage();

private:
	SettingsSubPage& m_settings_page;
	HTTPClient& m_http_client;
	std::string& m_hostname;
	IdType& m_user_id;


	const QString REGEX_PATTERN = "^[A-Z0-9a-z._-]{1,}@(\\w+)(\\.(\\w+))(\\.(\\w+))?(\\.(\\w+))?$";
	bool IsEmailValid(const QString& email) const;
	void AddVerification(const std::string& email);

public slots:
	void OnChangeEmail(const QString& old_email, const QString& new_email);
	void OnSetEmail(const std::string& email);

signals:
	void ServerError(const int code, const std::string& desc);
	void ClientError(const std::string& desc);
	void ChangeSubPage(MainSubPages page, PageData data=PageData{});

	void GoBack(int n=1);
};

