
#include "list.h"

//-----------------------------------------------------------------------------

int main()
{
    List<double> my_list("my_list");

    my_list.insert(position::BEFORE, 0, 28);
    my_list.insert(position::BEFORE, 0, 29);
   	// multiple constructors 
   	// construct list from array

    return 0;
}

