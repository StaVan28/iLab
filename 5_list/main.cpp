
#include "list.hpp"

//-----------------------------------------------------------------------------

int main()
{
	List my_list("my_list");

	my_list.push_tail(28);
	my_list.push_tail(1223);
	my_list.push_tail(23.12);
	my_list.push_tail(09.7);
	my_list.push_tail(88.1);
	my_list.push_tail(109120);
	my_list.push_tail(0.901111);
	my_list.push_tail(3.2);

	return 0;
}