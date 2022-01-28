
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdarg.h> 
#include <fstream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <algorithm>
#include <string.h>
#include <utility> 

//!

namespace Differenciator
{

static const char*       PATH_BUF_NODES_DUMP = "Txt/dump_BufNodes.txt";
static const std::string DEFAULT_SOURCE_TEXT = "./calc.txt";
static const std::size_t START_MAX_NODES     = 64;

};

//-----------------------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED
