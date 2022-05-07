#include "PasswordUpdateJSONParser.h"

PasswordUpdate PasswordUpdateJSONParser::Parse(const QJsonObject& json)
{
	PasswordUpdate password_update;
	SafeReadString(json, "code", password_update.code);
	SafeReadString(json, "password", password_update.password);
	return password_update;
}
