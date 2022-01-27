
#ifndef SYNTACTIC_ANALYSIS_H_INCLUDED
#define SYNTACTIC_ANALYSIS_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"
#include "tree.hpp"
#include "lexical_analysis.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

class Parser
{
    private:

        TextDiff buf_nodes_;
        Tree     syntax_tree_;

    public:

        Parser ();
       ~Parser ();

        Parser             (const Parser& other) = delete;
        Parser& operator = (const Parser& other) = delete;

        Parser             (Parser&& that) = delete;
        Parser& operator = (Parser&& that) = delete;

        NodeDiff get_expr ();
        NodeDiff get_term ();
        NodeDiff get_brck ();
        NodeDiff get_numb ();

}; // class Parser

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // SYNTACTIC_ANALYSIS_H_INCLUDED
