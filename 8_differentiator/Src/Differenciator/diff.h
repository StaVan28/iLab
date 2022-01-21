
#ifndef DIFFERENCIATOR_H_INCLUDED
#define DIFFERENCIATOR_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "tree.hpp"
#include "node_diff.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

class Diff
{
    private:

    public:

        Diff()
        {}

        Diff             (const Diff& other) = delete;
        Diff& operator = (const Diff& other) = delete;

        Diff             (Diff&& that) = delete;
        Diff& operator = (Diff&& that) = delete;

       ~Diff()
           {}

        NodeTree* diff (const NodeTree* input_node);
        NodeTree* copy (const NodeTree*  copy_node);
};

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // DIFFERENCIATOR_H_INCLUDED
