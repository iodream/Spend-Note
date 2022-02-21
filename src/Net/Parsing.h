#pragma once

#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include "../Exception.h"
#include "Server/libdal/Types.h"

class ParsingError : public Exception {
public:
	explicit ParsingError(const char* message)
		: Exception(message) {}

	explicit ParsingError(const std::string& message)
		: Exception(message) {}

	virtual ~ParsingError() noexcept {}
};


void SafeReadString(
	const QJsonObject& json,
	const std::string& label,
	std::string& dest);

void SafeReadString(
	const QJsonObject& json,
	const char* label,
	std::string& dest);

void SafeReadString(
	const QJsonObject& json,
	const std::string& label,
	QString& dest);

void SafeReadString(
	const QJsonObject& json,
	const char* label,
	QString& dest);

void SafeReadId(
	const QJsonObject& json,
	const char* label,
	db::IdType& dest);

void SafeReadId(
	const QJsonObject& json,
	const std::string& label,
	db::IdType& dest);

void SafeReadBigInt(
	const QJsonObject& json,
	const char* label,
	db::BigInt& dest);

void SafeReadiBgInt(
	const QJsonObject& json,
	const std::string& label,
	db::BigInt& dest);

void SafeReadMoney(
	const QJsonObject& json,
	const char* label,
	db::Money& dest);

void SafeReadMoney(
	const QJsonObject& json,
	const std::string& label,
	db::Money& dest);

void SafeReadNumber(
	const QJsonObject& json,
	const char* label,
	double& dest);

void SafeReadNumber(
	const QJsonObject& json,
	const std::string& label,
	double& dest);

void SafeReadArray(
	const QJsonObject& json,
	const char* label,
	QJsonArray& dest);

void SafeReadArray(
	const QJsonObject& json,
	const std::string& label,
	QJsonArray& dest);

void SafeReadBool(
	const QJsonObject& json,
	const char* label,
	bool& dest);

void SafeReadBool(
	const QJsonObject& json,
	const std::string& label,
	bool& dest);

void SafeReadObject(
	const QJsonObject& json,
	const char* label,
	QJsonObject& dest);

void SafeReadObject(
	const QJsonObject& json,
	const std::string& label,
	QJsonObject& dest);

double FormatId(db::IdType id);

void WriteId(
	QJsonObject& json,
	const char* label,
	const db::IdType& value);

void WriteId(
	QJsonObject& json,
	const std::string& label,
	const db::IdType& value);

void WriteBigInt(
	QJsonObject& json,
	const char* label,
	const db::BigInt& value);

void WriteBigInt(
	QJsonObject& json,
	const std::string& label,
	const db::BigInt& value);

void WriteMoney(
	QJsonObject& json,
	const char* label,
	const db::Money& value);

void WriteMoney(
	QJsonObject& json,
	const std::string& label,
	const db::Money& value);

void WriteNumber(
	QJsonObject& json,
	const char* label,
	const double& value);

void WriteNumber(
	QJsonObject& json,
	const std::string& label,
	const double& value);

void WriteString(
	QJsonObject& json,
	const char* label,
	const std::string& value);

void WriteString(
	QJsonObject& json,
	const std::string& label,
	const std::string& value);

void WriteString(
	QJsonObject& json,
	const char* label,
	const QString& value);

void WriteString(
	QJsonObject& json,
	const std::string& label,
	const QString& value);
