#pragma once

#include <string>
#include <stdexcept>
#include "pqxx/pqxx"

namespace db
{
class DatabaseFailure : public std::runtime_error
{
public:
	DatabaseFailure() : std::runtime_error("Database failed") {}
	DatabaseFailure(std::string& msg) : std::runtime_error(msg) {}
	DatabaseFailure(const char* msg) : std::runtime_error(msg) {}
};
}
