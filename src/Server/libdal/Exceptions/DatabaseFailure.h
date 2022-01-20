#pragma once

#include <stdexcept>
#include "pqxx/pqxx"

class DatabaseFailure : public std::runtime_error
{
public:
	DatabaseFailure();
};

