
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

       ~Diff()
       	{}

		NodeTree* diff (const NodeTree* input_node);
		NodeTree* copy (const NodeTree*  copy_node);
};

}; // namespace Differenciator

//-----------------------------------------------------------------------------

#endif // DIFFERENCIATOR_H_INCLUDED
