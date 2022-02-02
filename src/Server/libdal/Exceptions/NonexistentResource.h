#pragma once

#include "DatabaseFailure.h"

class NonexistentResource : public DatabaseFailure
{
public:
	NonexistentResource(std::string& msg) : DatabaseFailure(msg) {}
	NonexistentResource(const char* msg) : DatabaseFailure(msg) {}
};

