#include "syntactic_analysis.h"

//-----------

namespace Differenciator
{

//------

Parser::Parser () :
    buf_nodes_   {DEFAULT_SOURCE_TEXT},
    syntax_tree_ {DEFAULT_TREE_NAME}
{}

//------

Parser::~Parser ()
{}

//------

NodeDiff Parser::get_expr ()
{

}

//------

NodeDiff Parser::get_term ()
{

}

//------

NodeDiff Parser::get_brck ()
{

}
//------

NodeDiff Parser::get_numb ()
{

}

}; // namespace Differenciator

