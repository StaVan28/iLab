
#include "list.h"

//-----------------------------------------------------------------------------

int main()
{
    List<double> my_list("my_list");

    my_list.insert(position::BEFORE, 0, 21.5);

    return 0;
}

