#include "TokenJSONParser.h"

Token TokenJSONParser::Parse(const QJsonObject& json)
{
	Token token;
	SafeReadString(json, "token", token.token);
	return token;
}
