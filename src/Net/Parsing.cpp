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
