
#include "stack.h"

int main() {

    RECREATE_DUMP_STACK_FILE

    STACK_CONSTRUCT(stck3, 5);

    stack_push(&stck3, 1);

    stack_destruct(&stck3);

    return 0;
}

/*!TODO
    -- assert(stck)     DONE
    -- fix realloc      DONE
*/
