#pragma once

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

void SafeReadQString(
	const QJsonObject& json,
	const std::string& label,
	QString& dest);

void SafeReadQString(
	const QJsonObject& json,
	const char* label,
	QString& dest);

void SafeReadId(
	const QJsonObject& json,
	const char* label,
	IdType& dest);

void SafeReadId(
	const QJsonObject& json,
	const std::string& label,
	IdType& dest);

void SafeReadAmount(
	const QJsonObject& json,
	const char* label,
	BigInt& dest);

void SafeReadAmount(
	const QJsonObject& json,
	const std::string& label,
	BigInt& dest);

void SafeReadPrice(
	const QJsonObject& json,
	const char* label,
	Money& dest);

void SafeReadPrice(
	const QJsonObject& json,
	const std::string& label,
	Money& dest);

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

void SafeWriteId(
	QJsonObject& json,
	const char* label,
	IdType& dest);

void SafeWriteId(
	QJsonObject& json,
	const std::string& label,
	IdType& dest);

void SafeWriteAmount(
	QJsonObject& json,
	const char* label,
	BigInt& dest);

void SafeWriteAmount(
	QJsonObject& json,
	const std::string& label,
	BigInt& dest);

void SafeWritePrice(
	QJsonObject& json,
	const char* label,
	Money& dest);

void SafeWritePrice(
	QJsonObject& json,
	const std::string& label,
	Money& dest);
