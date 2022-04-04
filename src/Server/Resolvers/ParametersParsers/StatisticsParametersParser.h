#pragma once

#include <string>
#include "../Params.h"

class StatisticsParametersParser
{
public:
	void Parse(const std::string& segment, Params& params);
};
