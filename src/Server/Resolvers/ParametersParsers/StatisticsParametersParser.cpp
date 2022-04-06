#include "StatisticsParametersParser.h"

namespace {

const std::string TYPE  = "type";
const std::string PERIOD = "period";
const std::string FORMAT = "format";
const std::string ASSIGNMENT_OPERATOR = "=";
}

void StatisticsParametersParser::Parse(const std::string& segment, Params& params)
{
	auto type = segment.find(TYPE);
	auto period = segment.find(PERIOD);
	auto format = segment.find(FORMAT);
	if (type != std::string::npos && period != std::string::npos) {
		auto first_parameter = segment.substr(type, period - type - 1);
		auto second_parameter = segment.substr(period, format - period - 1);
		auto third_parameter = segment.substr(format);
		auto first_assigment = first_parameter.find("=");
		auto second_assigment = second_parameter.find("=");
		auto third_assigment = third_parameter.find("=");
		params.Insert(Params::STATISTICS_TYPE, Params::Value{first_parameter.substr(first_assigment + 1)});
		params.Insert(Params::STATISTICS_PERIOD, Params::Value{second_parameter.substr(second_assigment + 1)});
		params.Insert(Params::STATISTICS_FORMAT, Params::Value{third_parameter.substr(third_assigment + 1)});
	}
}
