#include "EmailUpdateJSONParser.h"

EmailUpdate EmailUpdateJSONParser::Parse(const QJsonObject& json)
{
	EmailUpdate email_update;
	SafeReadString(json, "code", email_update.code);
	SafeReadString(json, "email", email_update.email);
	return email_update;
}
