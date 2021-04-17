
#include "list.hpp"

//-----------------------------------------------------------------------------

int main()
{
	List my_list("my_list");


	my_list.push_head(33);
	my_list.push_head(28);

	my_list.push_tail(99);

	return 0;
}

