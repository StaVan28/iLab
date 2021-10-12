
#include "stack.h"

int main() {

    RECREATE_DUMP_STACK_FILE

	Stack test_stck("stck3", 5);

    test_stck.push(1);



    return 0;
}

/*!TODO
    -- assert(stck)     DONE
    -- fix realloc      DONE
*/
