#include "PasswordUpdateJSONFormatter.h"

QJsonDocument PasswordUpdateJSONFormatter::Format(const PasswordUpdate& password_update)
{
	QJsonObject json;
	WriteString(json, "code", password_update.code);
	WriteString(json, "password", password_update.password);
	return QJsonDocument(json);
}
