#include "syntactic_analysis.h"

//-----------

namespace Differenciator
{

//------

Parser::Parser () :
    buf_nodes_   (DEFAULT_SOURCE_TEXT, START_MAX_NODES),
    syntax_tree_ (DEFAULT_TREE_NAME)
{   
    i_node_ = 0;

    syntax_tree_.root_ = get_expr ();
}

//------

Parser::~Parser ()
{
    syntax_tree_.dump (Mode::DEBUG,   DEFAULT_TREE_DUMP_PATH);
    syntax_tree_.dump (Mode::RELEASE, DEFAULT_TREE_DUMP_PATH);
}

//------

NodeDiff* Parser::get_expr ()
{
    return nullptr;
}

//------

NodeDiff* Parser::get_term ()
{
    return nullptr;
}

//------

NodeDiff* Parser::get_prnt ()
{
    return nullptr;
}
//------

NodeDiff* Parser::get_numb ()
{

    return nullptr;
}

}; // namespace Differenciator

