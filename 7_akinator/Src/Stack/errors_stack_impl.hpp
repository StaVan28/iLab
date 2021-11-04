//-----------------------------------------------------------------------------

template <typename data_t>
int Stack<data_t>::error() {

    if (this == nullptr) {
        return NULL_PTR_STACK;
    } 

    if (cur_size_ < 0) {
        error_ = NEGATIVE_CURRENT_SIZE;
        return NEGATIVE_CURRENT_SIZE;
    }

    if (capacity_ < 0) {
        error_ = NEGATIVE_CAPACITY;
        return NEGATIVE_CAPACITY;
    }

    if (cur_size_ > capacity_) {
        error_ = CUR_SIZE_MORE_CAPACITY;
        return CUR_SIZE_MORE_CAPACITY;
    }

    if (data_ == nullptr) {
        error_ = NULL_PTR_DATA;
        return NULL_PTR_DATA;
    }

    if (error_ != 0)
        return HAVE_ERROR; 

    #ifdef DEFENCE_STACK
    if (*(int*)(data_ - 1 * sizeof(int)) != CANARY_LEFT_DATA) {
        error_ = CANARY_DATA_ERROR;
        return CANARY_DATA_ERROR;
    }

    if (*(int*)(data_ + capacity_ * sizeof(data_t)) != CANARY_RIGHT_DATA) {
        error_ = CANARY_DATA_ERROR;
        return CANARY_DATA_ERROR;
    }

    if (canary_left_stack_ != CANARY_LEFT_STACK) {
        error_ = CANARY_STACK_ERROR;
        return CANARY_STACK_ERROR;
    }

    if (canary_right_stack_ != CANARY_RIGHT_STACK) {
        error_ = CANARY_STACK_ERROR;
        return CANARY_STACK_ERROR;
    }

    if (hash_ != hash()) {
        error_ = HASH_ERROR;
        return HASH_ERROR;
    }
    #endif

    return SUCCESS;
}

//-----------------------------------------------------------------------------

template <typename data_t>
const char* Stack<data_t>::text_error(void) {
    switch(error_) {
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

//-----------------------------------------------------------------------------
