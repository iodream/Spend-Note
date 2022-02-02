#include "Utils.h"

std::string GetSegment(
	const std::string& path,
	std::string::size_type pos,
	std::string::size_type& next_pos)
{
	next_pos = path.find("/", pos + 1);
	auto domain = path.substr(pos, next_pos);
	return domain;
}
