#pragma once

#include "DatabaseFailure.h"

class SQLFailure : public DatabaseFailure
{
public:
	SQLFailure(std::string& msg) : DatabaseFailure(msg) {}
	SQLFailure(const char* msg) : DatabaseFailure(msg) {}
};

