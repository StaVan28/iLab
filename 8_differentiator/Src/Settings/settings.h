
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

//!

namespace Differenciator
{

static const char* PATH_BUF_TOKENS_DUMP = "Txt/dump_BufTokens.txt";

enum class TokenType : int
{   //   = _digit_ for debug  //
    ERROR = -1,
    NONE  = 0, 
    OPER  = 1,
    NUMB  = 2,
    VARB  = 3,
};

//!

struct TokenDiff
{
    TokenType type_;

    char value_oper_;
    long value_numb_;
    char value_varb_;

    TokenDiff ()
    {}

   ~TokenDiff ()
    {}

    void print_data (FILE* dump) const;

};

};

//-----------------------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED
