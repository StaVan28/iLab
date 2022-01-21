
#ifndef NODE_DIFF_H_INCLUDED
#define NODE_DIFF_H_INCLUDED

//-----------------------------------------------------------------------------

namespace Differenciator
{

enum class NodeType : int
{   //    = _digit_ for debug  //
    ERROR = -1,
    NONE  =  0, 
    OPER  =  1,
    NUMB  =  2,
    VARB  =  3,
};

//!----

struct NodeDiff
{
    NodeType type_;

    char value_oper_;
    long value_numb_;
    char value_varb_;

    NodeDiff ()
    {}

   ~NodeDiff ()
    {}

    void print_data (FILE* dump) const;

};

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // NODE_DIFF_H_INCLUDED
