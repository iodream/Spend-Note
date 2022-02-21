#pragma once

#include "DatabaseFailure.h"

namespace db
{
class NonexistentResource : public DatabaseFailure
{
public:
	NonexistentResource(const std::string& msg) : DatabaseFailure(msg) {}
	NonexistentResource(const char* msg) : DatabaseFailure(msg) {}
};
}
