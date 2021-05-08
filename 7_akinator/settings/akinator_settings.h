
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

const std::string AKINATOR_TREE_NAME = "akinator_tree";
const std::string DEFAULT_BASE       = "./txt/base_akinator.txt";

const int ALL_BUFFER = 32767;

const char   QUESTION_SIGN = '?';
const char     ANSWER_SIGN = '$';
const char BEGIN_NODE_SIGN = '?'; 
const char   END_NODE_SIGN = '$';

//-----------------------------------------------------------------------------

#endif // AKINATOR_SETTINGS_HPP_INCLUDED