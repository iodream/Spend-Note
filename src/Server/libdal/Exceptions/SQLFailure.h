#pragma once

#include "DatabaseFailure.h"

namespace db
{
class SQLFailure : public DatabaseFailure
{
public:
	SQLFailure(const std::string& msg) : DatabaseFailure(msg) {}
	SQLFailure(const char* msg) : DatabaseFailure(msg) {}
};
}
