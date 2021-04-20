
#include "tree.hpp"

//-----------------------------------------------------------------------------

int main()
{
	Tree my_tree;

	my_tree.insert("root");

	my_tree.insert("left");

	my_tree.insert("right");

	my_tree.dump();

    return 0;
}


