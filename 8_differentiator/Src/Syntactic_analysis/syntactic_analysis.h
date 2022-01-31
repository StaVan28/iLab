
#ifndef SYNTACTIC_ANALYSIS_H_INCLUDED
#define SYNTACTIC_ANALYSIS_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"
#include "lexical_analysis.h"
#include "tree.hpp"

//-----------------------------------------------------------------------------

namespace Differenciator
{

enum class Signs : char
{
    PLUS  = '+',
    MINUS = '-',
    MUL   = '*',
    DIV   = '/',
    LP    = '(',
    RP    = ')',
};

//!

class Parser
{
    private:

        BufNodes    buf_nodes_;
        Tree        syntax_tree_;
        std::size_t i_node_;

    public:

        Parser ();
       ~Parser ();

        Parser             (const Parser& other) = delete;
        Parser& operator = (const Parser& other) = delete;

        Parser             (Parser&& that) = delete;
        Parser& operator = (Parser&& that) = delete;

        NodeDiff* get_expr ();
        NodeDiff* get_term ();
        NodeDiff* get_prnt ();
        NodeDiff* get_numb ();

}; // class Parser

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // SYNTACTIC_ANALYSIS_H_INCLUDED
