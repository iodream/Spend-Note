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
	ConnectSettingsPage();

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

void SettingsPageController::ConnectSettingsPage()
{
	connect(
		&m_settings_page,
		&SettingsSubPage::ChangeEmail,
		this,
		&SettingsPageController::OnChangeEmail);

}

bool SettingsPageController::IsEmailValid(const QString& email) const
{
	QRegularExpression regex(EMAIL_REGEX, QRegularExpression::CaseInsensitiveOption);
		QRegularExpressionMatch match = regex.match(email);

		if (match.hasMatch())
			return true;
		return false;
}

void SettingsPageController::AddVerification(const std::string& email)
{
	AddVerificationModel verification_model(m_hostname);
	AddVerificationModel::VerificationInDTO add_verification_dto;
	add_verification_dto.email = email;
	Net::Request request = verification_model.FormRequest(add_verification_dto);
	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch(Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
	}
}

void SettingsPageController::OnChangeEmail(const QString& old_email, const QString& new_email)
{
	if(new_email.isEmpty())
	{
		emit ClientError("Email should not be empty");
		return;
	}
	if (!IsEmailValid(new_email))
	{
		emit ClientError("Type valid email!");
		return;
	}

	AddVerification(old_email.toStdString());

	bool isOkPressed;

	QMessageBox::information(
		&m_settings_page,
		tr("Spend&Note"),
		tr("Verification code has been sent on ") + old_email);
	QString code = QInputDialog::getText(
		&m_settings_page,
		tr("Input your verification code"),
		tr("Code: "),
		QLineEdit::Normal,
		"", &isOkPressed); // "" field is empty since we will not use default text for code label

	if(!isOkPressed)
	{
		emit ClientError("Cannot update email without verification!");
		return;
	}

	ChangeEmailModel model(m_hostname);
	EmailUpdate email_update{code.toStdString(), new_email.toStdString()};
	Net::Request request = model.FormRequest(email_update, m_user_id);
	Net::Response response;
	try
	{
		response = m_http_client.Request(request);
	}
	catch (Poco::Exception& exc)
	{
		return;
	}

	if(response.status >= Poco::Net::HTTPResponse::HTTP_BAD_REQUEST)
	{
		emit ServerError(response.status, response.reason);
		return;
	}

	OnSetEmail(new_email.toStdString());

	QMessageBox::information(
		&m_settings_page,
		tr("Spend&Note"),
		tr("Your email has been updated"));
}


void SettingsPageController::OnSetEmail(const std::string& email)
{
	m_settings_page.SetEmail(QString::fromStdString(email));
}
