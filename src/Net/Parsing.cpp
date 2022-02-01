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
	if (json.contains(label) && json[label].isDouble()) {
		double id = json[label].toDouble();
		double* ptr = &id;
		IdType* value = reinterpret_cast<IdType*>(ptr);
		dest = *value;
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

void SafeReadAmount(
	const QJsonObject& json,
	const char* label,
	BigInt& dest)
{
	if (json.contains(label) && json[label].isDouble()) {
		double amount = json[label].toDouble();
		double* ptr = &amount;
		BigInt* value = reinterpret_cast<BigInt*>(ptr);
		dest = *value;
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadAmount(
	const QJsonObject& json,
	const std::string& label,
	IdType& dest)
{
	return SafeReadAmount(json, label.c_str(), dest);
}

void SafeReadPrice(
	const QJsonObject& json,
	const char* label,
	Money& dest)
{
	if (json.contains(label) && json[label].isDouble()) {
		double price = json[label].toDouble();
		double* ptr = &price;
		Money* value = reinterpret_cast<Money*>(ptr);
		dest = *value;
	}
	else {
		throw ParsingError{
			std::string{"Failed to parse \""}.append(label).append("\" field")};
	}
}

void SafeReadPrice(
	const QJsonObject& json,
	const std::string& label,
	IdType& dest)
{
	return SafeReadPrice(json, label.c_str(), dest);
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

void SafeWriteId(
	QJsonObject& json,
	const char* label,
	IdType& dest)
{
	double* id = reinterpret_cast<double*>(dest);
	json[label] = *id;

}

void SafeWriteId(
	QJsonObject& json,
	const std::string& label,
	IdType& dest)
{
	return SafeReadId(json, label.c_str(), dest);
}

void SafeWriteAmount(
	QJsonObject& json,
	const char* label,
	BigInt& dest)
{
	double* amount = reinterpret_cast<double*>(dest);
	json[label] = *amount;

}

void SafeWriteAmount(
	QJsonObject& json,
	const std::string& label,
	BigInt& dest)
{
	return SafeReadId(json, label.c_str(), dest);
}

void SafeWritePrice(
	QJsonObject& json,
	const char* label,
	Money& dest)
{
	double* price = reinterpret_cast<double*>(dest);
	json[label] = *price;

}

void SafeWritePrice(
	QJsonObject& json,
	const std::string& label,
	Money& dest)
{
	return SafeReadId(json, label.c_str(), dest);
}
