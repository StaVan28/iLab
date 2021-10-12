
#ifndef SETTINGS_TREE_HPP_INCLUDED
#define SETTINGS_TREE_HPP_INCLUDED

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

//!
enum class Position : int
{
	RIGHT,
	LEFT,
};

//-----------------------------------------------------------------------------

static const std::string UNKNOWN_NAME = "UNKNOWN NAME";

static const int EMPTY = 0; 

//-----------------------------------------------------------------------------

std::string current_time_and_date();

#endif // SETTINGS_TREE_HPP_INCLUDED