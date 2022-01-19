#pragma once

#include <QJsonDocument>
#include <QJsonObject>

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

void SafeReadId(
	const QJsonObject& json,
	const char* label,
	IdType& dest);

void SafeReadId(
	const QJsonObject& json,
	const std::string& label,
	IdType& dest);
