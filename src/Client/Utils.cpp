 #include "Utils.h"

std::string EraseWhitespace(std::string str)
{
	str.erase(std::remove_if(str.begin(), str.end(), ::isspace)
			, str.end());
	return str;
}
