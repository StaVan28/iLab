
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

        Diff (const char* source_text = DEFAULT_SOURCE_TEXT);
       ~Diff ();

        Diff             (const Diff& other) = delete;
        Diff& operator = (const Diff& other) = delete;

        Diff             (Diff&& that) = delete;
        Diff& operator = (Diff&& that) = delete;

        NodeTree* diff (const NodeTree* input_node);
        NodeTree* copy (const NodeTree*  copy_node);

}; // class Diff

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // DIFFERENCIATOR_H_INCLUDED
