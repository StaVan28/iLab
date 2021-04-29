
#include "tree.hpp"

//-----------------------------------------------------------------------------

int main()
{
	Tree my_tree("my_tree");
	my_tree.insert("7");
	my_tree.insert("9");
	my_tree.insert("2");

	my_tree.insert("1");
	my_tree.insert("4");

	my_tree.insert("3");
	my_tree.insert("5");

	my_tree.insert("5.5");

	my_tree.remove("2");

	my_tree.dump(Mode::DEBUG);

    return 0;
}


