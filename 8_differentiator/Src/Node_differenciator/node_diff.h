
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

    //!-----

    NodeDiff ()
    {}

    //!

   ~NodeDiff ()
    {}

    //!

    NodeDiff (const NodeDiff& other) :
        type_       {other.type_},
        value_oper_ {other.value_oper_},
        value_numb_ {other.value_numb_},
        value_varb_ {other.value_varb_}
    {}

    //!

    NodeDiff& operator = (const NodeDiff& other)
    {
        NodeDiff copy (other);
        swap (*this, copy);

        return *this;
    }

    //!

    NodeDiff (NodeDiff&& that) noexcept :
        type_       {NodeType::NONE},
        value_oper_ {0},
        value_numb_ {0},
        value_varb_ {0}
    {
        swap (*this, that);
    }

    //!

    NodeDiff& operator = (NodeDiff&& that) noexcept
    {
        swap(*this, that);

        return *this;
    }

    //!

    void print_data (FILE* dump) const;

    friend void swap (NodeDiff& lhs, NodeDiff& rhs) noexcept
    {
        std::swap (lhs.type_      , rhs.type_);
        std::swap (lhs.value_oper_, rhs.value_oper_);
        std::swap (lhs.value_numb_, rhs.value_numb_);
        std::swap (lhs.value_varb_, rhs.value_varb_);
    }

}; // class NodeDiff

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // NODE_DIFF_H_INCLUDED
