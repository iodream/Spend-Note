#pragma once

#include "DatabaseFailure.h"

namespace db
{
class NonexistentResource : public DatabaseFailure
{
public:
	NonexistentResource(std::string& msg) : DatabaseFailure(msg) {}
	NonexistentResource(const char* msg) : DatabaseFailure(msg) {}
};
}
