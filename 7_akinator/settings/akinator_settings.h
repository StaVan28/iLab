
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
    EXIT       = 0,
    GUESS_MODE = 1,
};

//!

enum class PositionNode : int
{
    LEFT,
    RIGHT,
    ROOT,
};

//-----------------------------------------------------------------------------

const std::string DEFAULT_BASE       = "./txt/base_akinator.txt";
const std::string AKINATOR_TREE_NAME = "Akinator Tree";

const int ALL_BUFFER = 32767;

//-----------------------------------------------------------------------------

#endif // AKINATOR_SETTINGS_HPP_INCLUDED