#pragma once

#include <string>
#include "Types.h"

namespace db
{
	struct VerificationCode
	{
		IdType id;
		IdType user_id;
		std::string code;
		Timestamp expiration_time;
	};
}
