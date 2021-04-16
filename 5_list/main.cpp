
#include "list.hpp"

//-----------------------------------------------------------------------------

int main()
{
	List my_list("my_list");

	my_list.push_tail(28);
	my_list.push_tail(1223);
	my_list.pop_tail();

	return 0;
}