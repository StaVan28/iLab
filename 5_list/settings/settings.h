
#ifndef SETTINGS_HPP_INCLUDED
#define SETTINGS_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <cmath>

//-----------------------------------------------------------------------------

enum class position : int {
    BEFORE = 28,
    AFTER  = 29,
};

//-----------------------------------------------------------------------------

static const char* UNKNOWN_NAME = "UNKNOWN NAME";

static const int EMPTY = 0;

static const int  NO_ELEMENT = 0;
static const int ONE_ELEMENT = 1;

static char*  STRING_POISON = nullptr;
static double DOUBLE_POISON = NAN;

//-----------------------------------------------------------------------------

#endif // SETTINGS_HPP_INCLUDED