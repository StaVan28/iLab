
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

//-----------------------------------------------------------------------------

#include <cstdio>
#include <cstdarg> 
#include <fstream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <cerrno>
#include <cstdbool>
#include <algorithm>
#include <utility> 

//!

namespace Differenciator
{

static const std::string& PATH_BUF_NODES_DUMP = "Txt/dump_BufNodes.txt";
static const std::string& DEFAULT_SOURCE_TEXT = "./calc.txt";
static const std::string& DEFAULT_TREE_NAME   = "syntax_tree_diff";

static const std::size_t START_MAX_NODES      = 64;

};

//-----------------------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED
