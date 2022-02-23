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

void SafeReadString(
	const QJsonObject& json,
	const std::string& label,
	QString& dest)
{
	return SafeReadString(json, label.c_str(), dest);
}

void SafeReadString(
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
	db::IdType& dest)
{
	if (json.contains(label) && json[label].isDouble()) {
		dest = json[label].toDouble();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadId(
	const QJsonObject& json,
	const std::string& label,
	db::IdType& dest)
{
	return SafeReadId(json, label.c_str(), dest);
}

void SafeReadBigInt(
	const QJsonObject& json,
	const char* label,
	db::BigInt& dest)
{
	if (json.contains(label) && json[label].isDouble())
	{
		dest = json[label].toDouble();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadBigInt(
	const QJsonObject& json,
	const std::string& label,
	db::IdType& dest)
{
	return SafeReadBigInt(json, label.c_str(), dest);
}

void SafeReadMoney(
	const QJsonObject& json,
	const char* label,
	db::Money& dest)
{
	if (json.contains(label) && json[label].isDouble()) {
		dest = json[label].toDouble();
	}
	else
	{
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadMoney(
	const QJsonObject& json,
	const std::string& label,
	db::IdType& dest)
{
	return SafeReadMoney(json, label.c_str(), dest);
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

void SafeReadObject(
	const QJsonObject& json,
	const char* label,
	QJsonObject& dest)
{
	if (json.contains(label) && json[label].isObject()) {
		dest = json[label].toObject();
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadObject(
	const QJsonObject& json,
	const std::string& label,
	QJsonObject& dest)
{
	return SafeReadObject(json, label.c_str(), dest);
}

double FormatId(db::IdType id)
{
	return id;
}

void WriteId(
	QJsonObject& json,
	const char* label,
	const db::IdType& value)
{
	json[label] = FormatId(value);
}

void WriteId(
	QJsonObject& json,
	const std::string& label,
	const db::IdType& value)
{
	return WriteId(json, label.c_str(), value);
}

void WriteBigInt(
	QJsonObject& json,
	const char* label,
	const db::BigInt& value)
{
	json[label] = value;
}

void WriteBigInt(
	QJsonObject& json,
	const std::string& label,
	const db::BigInt& value)
{
	return WriteBigInt(json, label.c_str(), value);
}

void WriteMoney(
	QJsonObject& json,
	const char* label,
	const db::Money& value)
{
	json[label] = value;
}

void WriteMoney(
	QJsonObject& json,
	const std::string& label,
	const db::Money& value)
{
	return WriteMoney(json, label.c_str(), value);
}

void WriteNumber(
	QJsonObject& json,
	const char* label,
	const double& value)
{
	json[label] = value;
}

void WriteNumber(
	QJsonObject& json,
	const std::string& label,
	const double& value)
{
	return WriteNumber(json, label.c_str(), value);
}

void WriteString(
	QJsonObject& json,
	const char* label,
	const std::string& value)
{
	json[label] = value.c_str();
}

void WriteString(
	QJsonObject& json,
	const std::string& label,
	const std::string& value)

{
	return WriteString(json, label.c_str(), value);
}

void WriteString(
	QJsonObject& json,
	const char* label,
	const QString& value)
{
	json[label] = value.toStdString().c_str();
}

void WriteString(
	QJsonObject& json,
	const std::string& label,
	const QString& value)
{
	return WriteString(json, label.c_str(), value);
}
