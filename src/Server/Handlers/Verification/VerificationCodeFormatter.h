#pragma once

#include <string>

class VerificationCodeFormatter
{
public:
	VerificationCodeFormatter() = default;
	~VerificationCodeFormatter() = default;
	const std::string FormatVerificationCode(const size_t length);
};


