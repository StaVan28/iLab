
#ifndef SETTINGS_HPP_INCLUDED
#define SETTINGS_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <chrono>  
#include <ctime>  
#include <sstream> 
#include <iomanip> 
#include <string>  

//-----------------------------------------------------------------------------

enum class Mode : int 
{
	DEBUG,
	RELEASE,
};

//-----------------------------------------------------------------------------

static const std::string UNKNOWN_NAME    = "UNKNOWN NAME";
static const std::string COMPILE_DOT_CMD = "dot -Tjpeg ./txt/graph_tree.dot -o";

//-----------------------------------------------------------------------------

std::string return_current_time_and_date();

#endif // SETTINGS_HPP_INCLUDED