#pragma once

#include <stdexcept>

class DatabaseFailure : public std::runtime_error
{
public:
	DatabaseFailure();
};

