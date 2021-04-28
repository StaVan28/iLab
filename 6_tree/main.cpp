
#include "tree.hpp"

//-----------------------------------------------------------------------------

int main()
{
	Tree my_tree("my_tree");

	my_tree.insert("hi");
	my_tree.insert("прывитанне");
	my_tree.insert("hola");

	my_tree.insert("გამარჯობა");
	my_tree.insert("hello");
	my_tree.insert("любовь");

	std::string max;
	if (my_tree.find_max(max))
		std::cout << max << std::endl << std::endl;
	else 
		std::cout << "gggggggggggggggggggggggggggggg" << std::endl;

	my_tree.dump(Mode::DEBUG);

    return 0;
}


