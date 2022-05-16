#include "TokenJSONFormatter.h"

QJsonDocument TokenJSONFormatter::Format(const Token& token)
{
	QJsonObject json;
	WriteString(json, "token", token.token);
	return QJsonDocument(json);
}
