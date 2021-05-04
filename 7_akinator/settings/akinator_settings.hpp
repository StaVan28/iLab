
#ifndef AKINATOR_SETTINGS_HPP_INCLUDED
#define AKINATOR_SETTINGS_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

//-----------------------------------------------------------------------------

enum AkinatorModes
{
    Guess_mode = 1,
};

//-----------------------------------------------------------------------------

const std::string AKINATOR_TREE_NAME = "akinator_tree";
const std::string DEFAULT_BASE       = "./txt/base_akinator.txt";

static const int ALL_BUFFER = 32767;

//-----------------------------------------------------------------------------

#endif // AKINATOR_SETTINGS_HPP_INCLUDED