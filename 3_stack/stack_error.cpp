
#include "stack.h"

//-----------------------------------------------------------------------------

int stack_error(my_stack_t *stck) {

    if (stck == nullptr) {
        return NULL_PTR_STACK;
    } 

    if (stck->cur_size < 0) {
        stck->error = NEGATIVE_CURRENT_SIZE;
        return NEGATIVE_CURRENT_SIZE;
    }

    if (stck->capacity < 0) {
        stck->error = NEGATIVE_CAPACITY;
        return NEGATIVE_CAPACITY;
    }

    if (stck->cur_size > stck->capacity) {
        stck->error = CUR_SIZE_MORE_CAPACITY;
        return CUR_SIZE_MORE_CAPACITY;
    }

    if (stck->data == nullptr) {
        stck->error = NULL_PTR_DATA;
        return NULL_PTR_DATA;
    }

    if (stck->error != 0)
        return HAVE_ERROR; 

    #ifdef DEFENCE_STACK
    if (*(int*)(stck->data - 1 * sizeof(int)) != CANARY_LEFT_DATA) {
        stck->error = CANARY_DATA_ERROR;
        return CANARY_DATA_ERROR;
    }

    if (*(int*)(stck->data + stck->capacity * sizeof(double)) != CANARY_RIGHT_DATA) {
        stck->error = CANARY_DATA_ERROR;
        return CANARY_DATA_ERROR;
    }

    if (stck->canary_left_stack != CANARY_LEFT_STACK) {
        stck->error = CANARY_STACK_ERROR;
        return CANARY_STACK_ERROR;
    }

    if (stck->canary_right_stack != CANARY_RIGHT_STACK) {
        stck->error = CANARY_STACK_ERROR;
        return CANARY_STACK_ERROR;
    }

    if (stck->hash_ != stack_hash(stck)) {
        stck->error = HASH_ERROR;
        return HASH_ERROR;
    }
    #endif

    return SUCCESS;
}

//-----------------------------------------------------------------------------

const char* stack_text_error(my_stack_t *stck) {
    switch(stck->error) {
        case NEGATIVE_CURRENT_SIZE:
            return "NEGATIVE CURRENT SIZE";
        case NEGATIVE_CAPACITY:
            return "NEGATIVE CAPACITY";
        case CUR_SIZE_MORE_CAPACITY:
            return "CURRENT SIZE MORE CAPACITY";
        case NULL_PTR_DATA:
            return "NULL_PTR_DATA";
        case UNKNOW_NUMBER_CONSTRUCT:
            return "UNKNOW NUMBER CONSTRUCT";
        case UNKNOWN_NUMBER:
            return "NAN in stack";
        case CANARY_DATA_ERROR:
            return "CANARY DATA ERROR";
        case CANARY_STACK_ERROR:
            return "CANARY STACK ERROR";
        case HASH_ERROR:
            return "HASH ERROR";
        case REALLOC_ERROR:
            return "REALLOC ERROR: Your push sooo big!";
        case CALLOC_ERROR:
            return "CALLOC_ERROR: Calloc func didn't work";
        case CONSTRUCT_ERROR:
            return "CONSTRUCT ERROR: You initialization stack again";
        default:
            return "NULL PTR STACK";
    }

}
