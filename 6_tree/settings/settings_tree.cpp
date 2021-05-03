
#include "settings_tree.h"

//-----------------------------------------------------------------------------

std::string current_time_and_date()
{
	auto now       = std::chrono::system_clock::now();
	auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream str_stream;
	str_stream << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
	
	return str_stream.str();
}

