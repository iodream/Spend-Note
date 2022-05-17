#include "EmailUpdateJSONFormatter.h"

QJsonDocument EmailUpdateJSONFormatter::Format(const EmailUpdate& email_update)
{
	QJsonObject json;
	WriteString(json, "code", email_update.code);
	WriteString(json, "email", email_update.email);
	return QJsonDocument(json);
}
