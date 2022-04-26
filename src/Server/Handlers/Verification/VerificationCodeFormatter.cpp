#include <algorithm>

#include "VerificationCodeFormatter.h"

const std::string VerificationCodeFormatter::FormatVerificationCode(const size_t length)
{
	auto randchar = []() -> char
	{
		const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[ rand() % max_index ];
	};
	std::string code(length,0);
	std::generate_n(code.begin(), length, randchar);
	return code;
}
