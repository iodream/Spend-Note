#include <algorithm>
#include <random>

#include "VerificationCodeFormatter.h"

const std::string VerificationCodeFormatter::FormatVerificationCode(const size_t length)
{
	auto rand_char = []() -> char
	{
		std::string char_set =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";	
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<> dist(0, char_set.size());
		return char_set[int(dist(mt))];
	};
	std::string code(length,0);
	std::generate_n(code.begin(), length, rand_char);
	return code;
}
