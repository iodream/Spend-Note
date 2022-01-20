#include "DatabaseFailure.h"

DatabaseFailure::DatabaseFailure() : std::runtime_error("Database failed")
{
}
