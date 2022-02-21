#pragma once

#include <string>
#include <algorithm>
#include <QString>
#include <QDateTime>

std::string EraseWhitespace(std::string str);
QString toDBstring(const QDateTime& time);
