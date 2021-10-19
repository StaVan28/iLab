#ifndef SETTINGS
#define SETTINGS

//--------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string>
#include <chrono>  
#include <ctime>  
#include <sstream> 
#include <iomanip>
#include <fstream> 
 
//--------------------------------------------------

const std::string DEFAULT_PATH_BASE = "./Txt/akinator_base.txt";
const int         EMPTY             = 0;

//--------------------------------------------------

std::string current_time_and_date();

//--------------------------------------------------

#endif //SETTINGS
