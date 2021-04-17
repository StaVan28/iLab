
#include "list.hpp"

//-----------------------------------------------------------------------------

int main()
{
	List my_list("my_list");


	my_list.push_head(30);
	my_list.push_head(28);
	my_list.push_tail(32);

	return 0;
}

