#pragma once

#include <string>

#include "../Params.h"

std::string GetSegment(
	const std::string& path,
	std::string::size_type pos,
	std::string::size_type& next_pos);

void SafeInsertParam(
	const std::string& name,
	Params& params,
	Params::Value&& value);
