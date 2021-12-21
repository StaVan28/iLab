
#ifndef DIFFERENCIATOR_H_INCLUDED
#define DIFFERENCIATOR_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "tree.hpp"

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

};

//!

//-----------------------------------------------------------------------------

#endif // DIFFERENCIATOR_H_INCLUDED
