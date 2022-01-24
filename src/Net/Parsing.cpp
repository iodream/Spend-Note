#include "Parsing.h"

void SafeReadString(
    const QJsonObject& json,
    const std::string& label,
    std::string& dest)
{
    return SafeReadString(json, label.c_str(), dest);
}

void SafeReadString(
    const QJsonObject& json,
    const char* label,
    std::string& dest)
{
    if (json.contains(label) && json[label].isString()) {
        dest = json[label].toString().toStdString();
    }
    else {
        throw ParsingError{
            std::string{"Failed to parse \""}.append(label).append("\" field")};
    }
}

void SafeReadQString(
	const QJsonObject& json,
	const std::string& label,
	QString& dest)
{
	return SafeReadQString(json, label.c_str(), dest);
}

void SafeReadQString(
	const QJsonObject& json,
	const char* label,
	QString& dest)
{
	if (json.contains(label) && json[label].isString()) {
		dest = json[label].toString();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadId(
	const QJsonObject& json,
	const char* label,
	IdType& dest)
{
	if (json.contains(label) && json[label].isString()) {
		dest = json[label].toString().toLongLong();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadId(
	const QJsonObject& json,
	const std::string& label,
	IdType& dest)
{
	return SafeReadId(json, label.c_str(), dest);
}

void SafeReadNumber(
	const QJsonObject& json,
	const char* label,
	double& dest)
{
	if (json.contains(label) && json[label].isDouble()) {
		dest = json[label].toDouble();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadNumber(
	const QJsonObject& json,
	const std::string& label,
	double& dest)
{
	return SafeReadNumber(json, label.c_str(), dest);
}

void SafeReadArray(
	const QJsonObject& json,
	const char* label,
	QJsonArray& dest)
{
	if (json.contains(label) && json[label].isArray()) {
		dest = json[label].toArray();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadArray(
	const QJsonObject& json,
	const std::string& label,
	QJsonArray& dest)
{
	return SafeReadArray(json, label.c_str(), dest);
}

void SafeReadBool(
	const QJsonObject& json,
	const char* label,
	bool& dest)
{
	if (json.contains(label) && json[label].isBool()) {
		dest = json[label].toBool();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadBool(
	const QJsonObject& json,
	const std::string& label,
	bool& dest)
{
	return SafeReadBool(json, label.c_str(), dest);
}

