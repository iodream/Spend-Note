#include "StatisticsParametersParser.h"

namespace {

const std::string TYPE  = "type";
const std::string PERIOD = "period";
const std::string ASSIGNMENT_OPERATOR = "=";
}

void StatisticsParametersParser::Parse(const std::string& segment, Params& params)
{
	auto type = segment.find(TYPE);
	auto period = segment.find(PERIOD);
	if (type != std::string::npos && period != std::string::npos) {
		auto first_parametr = segment.substr(type, period - type - 1);
		auto second_parametr = segment.substr(period);
		auto first_assigment = first_parametr.find("=");
		auto second_assigment = second_parametr.find("=");
		params.Insert(Params::STATISTICS_TYPE, Params::Value{first_parametr.substr(first_assigment + 1)});
		params.Insert(Params::STATISTICS_PERIOD, Params::Value{second_parametr.substr(second_assigment + 1)});
	}
}
