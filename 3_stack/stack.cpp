

#include "stack.h"

//-----------------------------------------------------------------------------

static error_stack_t error_info = {};

//-----------------------------------------------------------------------------

Stack::Stack(const char* name, int capacity) {

    RECREATE_DUMP_STACK_FILE

    if (canary_left_stack_ != 0) {

        error_ = CONSTRUCT_ERROR;
        ERROR_INFO

        return;
    }

   if (this) {

        error_ = NULL_PTR_STACK;
       ERROR_INFO

        return;
    }

    if (capacity < 0) {

        error_ = UNKNOWN_NUMBER;
        ERROR_INFO

        return;
    }

    // Stack *temp_stck = this;       ?????? как переаллочить стек

    #ifdef DEFENCE_STACK
        data_ = (char*) calloc(capacity * sizeof(double) + TWO_CANARIES * sizeof(int), sizeof(char));
    #else
        data_ = (char*) calloc(capacity * sizeof(double), sizeof(char));
    #endif

    if (data_ == nullptr) {
        //this = temp_stck;           ?????? как переаллочить стек
        error_ = CALLOC_ERROR;
        ERROR_INFO
        return;
    }

    #ifdef DEFENCE_STACK
        data_ += sizeof(int);

        *(int*)(data_ - 1 * sizeof(int))           = CANARY_LEFT_DATA;
        *(int*)(data_ + capacity * sizeof(double)) = CANARY_RIGHT_DATA;
    #endif

    capacity_ = capacity;

    for (int indx = 0; indx < capacity_; indx++)
        *(double*)(data_ + indx * sizeof(double)) = POISON_DOUBLE_STACK;

    cur_size_ = 0;

    strcpy(name_, name);

    error_ = 0;

    #ifdef DEFENCE_STACK
        hash_ = hash();

        canary_left_stack_  = CANARY_LEFT_STACK;
        canary_right_stack_ = CANARY_RIGHT_STACK;
    #endif

    ASSERT_STACK_OK({return;})
}

//-----------------------------------------------------------------------------

void Stack::push(double data) {

    ASSERT_STACK_OK({return;})

    if (!isfinite(data)) {

        error_ = UNKNOWN_NUMBER;
        ERROR_INFO

        return;
    }

    int status_realloc = SUCCESS;

    if (cur_size_ == capacity_ || capacity_ < CAPACITY_MIN)
        status_realloc = realloc_data();

    if (status_realloc == SUCCESS) {
        *(double*)(data_ + cur_size_ * sizeof(double)) = data;
        cur_size_++;
    }

    #ifdef DEFENCE_STACK
        hash_ = hash();
    #endif

    ASSERT_STACK_OK({return;})
}

//-----------------------------------------------------------------------------

double Stack::pop(void) {

    ASSERT_STACK_OK({return POISON_DOUBLE_STACK;})

    int status_realloc = SUCCESS;

    if (capacity_ > CAPACITY_MIN && cur_size_ * CAPACITY_DIF < capacity_)
        status_realloc = realloc_data();

    double temp_data = 0;

    if (status_realloc == SUCCESS) {
        cur_size_--;
        temp_data = *(double*)(data_ + cur_size_ * sizeof(double));
        
        if (cur_size_ >= 0)
            *(double*)(data_ + cur_size_ * sizeof(double)) = POISON_DOUBLE_STACK;
    }

    #ifdef DEFENCE_STACK
        hash_ = hash();
    #endif

    ASSERT_STACK_OK({return POISON_DOUBLE_STACK;})

    return temp_data;
}

//-----------------------------------------------------------------------------

Stack::~Stack(void) {

    ASSERT_STACK_OK()

    dump();

    canary_left_stack_ = POISON_INT_STACK;

    for (int indx = 0; indx < capacity_; indx++)
        *(double*)(data_ + indx * sizeof(double)) = POISON_INT_STACK;

    capacity_ = POISON_INT_STACK;
    cur_size_ = POISON_INT_STACK;

    #ifdef DEFENCE_STACK
        data_ -= sizeof(int);
    #endif

    free(data_);
    data_ = nullptr;

    hash_ = POISON_INT_STACK;

    canary_right_stack_ = POISON_INT_STACK;
}

//-----------------------------------------------------------------------------

int Stack::realloc_data(void) {

    ASSERT_STACK_OK({return POISON_INT_STACK;})

    int temp_capacity = capacity_;

    if (capacity_ < CAPACITY_MIN)
        capacity_  = CAPACITY_MIN;
    else if (cur_size_ * CAPACITY_DIF < capacity_)
        capacity_ /= 2;
    else
        capacity_ *= 2;

    char *temp_stck_data = data_;

    #ifdef DEFENCE_STACK
        data_ -= sizeof(int);
        data_  = (char*) realloc(data_, capacity_ * sizeof(double) + TWO_CANARIES * sizeof(int));
    #else
        data_  = (char*) realloc(data_, capacity_ * sizeof(double));
    #endif

    if (data_ == nullptr) {

        data_  = temp_stck_data;

        error_ = REALLOC_ERROR;
        ERROR_INFO

        return REALLOC_ERROR;
    }

    #ifdef DEFENCE_STACK
        data_ += sizeof(int);
    #endif

    for (int indx = temp_capacity; indx < capacity_; indx++)
        *(double*)(data_ + indx * sizeof(double)) = POISON_DOUBLE_STACK;

    #ifdef DEFENCE_STACK
        *(int*)(data_ + capacity_ * sizeof(double)) = CANARY_RIGHT_DATA;
        hash_ = hash();
    #endif

    ASSERT_STACK_OK({return POISON_INT_STACK;})

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int Stack::hash(void) {

    int hash_ = POISON_INT_STACK;

    for (int indx = 0; indx < cur_size_; indx++) {

        hash_ = hash_ + (int)(data_[indx * sizeof(double)]);

        if (indx % 2) {
            hash_  |= cur_size_;
            hash_ <<= capacity_;
            hash_  |= *(name_);
        }
        else {
            hash_  |= capacity_;
            hash_ <<= cur_size_;
            hash_  |= *(name_);
        }
    }

    return hash_;
}

//-----------------------------------------------------------------------------

void Stack::dump(void) {


    FILE* dump_stack = fopen("./txt/dump_stack.txt", "ab");
    assert(dump_stack);

    PRINT_DIVIDING_DUMP_STACK_STRIP

    fprintf(dump_stack, "       Stack:\n\n");

    if (!error_)
        fprintf(dump_stack, "Stack (OK) [%p] \"%s\" {\n\n", this, name_);
    else {
        fprintf(dump_stack, "Stack (ERROR %d : %s) [%p] \"%s\" {\n", error_, text_error(), this, name_);
        fprintf(dump_stack, "In File : %s, LINE : %d\n", error_info.file, error_info.line);
        fprintf(dump_stack, "In Function : %s\n\n",    error_info.func);

        printf(             "Stack (ERROR %d : %s) [%p] \"%s\" {\n", error_, text_error(), this, name_);
        printf(             "In File : %s, LINE : %d\n", error_info.file, error_info.line);
        printf(             "In Function : %s\n\n",    error_info.func);
    }

    #ifdef DEFENCE_STACK
        fprintf(dump_stack, "Canary left  = %d  [%p]\n", canary_left_stack_, &(canary_left_stack_));
    #endif
    fprintf(dump_stack, "Current size = %d\n", cur_size_);
    fprintf(dump_stack, "Capacity     = %d\n", capacity_);
    #ifdef DEFENCE_STACK
        fprintf(dump_stack, "Hash         = %d\n", hash_);
        fprintf(dump_stack, "Canary right = %d  [%p]\n", canary_right_stack_, &(canary_right_stack_));
    #endif

    fprintf(dump_stack, "\nData [%p]\n", data_);

    if (capacity_ != POISON_INT_STACK) {
        #ifdef DEFENCE_STACK
            fprintf(dump_stack, " {canary_left} : %d  [%p]\n\n", *(int*)(data_ - 1 * sizeof(int)), \
                                                                  (int*)(data_ - 1 * sizeof(int)));
        #endif

        int indx = 0;
        for ( ; indx < cur_size_; indx++)
            fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(data_ + indx * sizeof(double)));
        for ( ; indx < capacity_; indx++)
            fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(data_ + indx * sizeof(double)));

        #ifdef DEFENCE_STACK
            fprintf(dump_stack, "\n {canary_right} : %d  [%p]\n", *(int*)(data_ + capacity_ * sizeof(double)), \
                                                                   (int*)(data_ + capacity_ * sizeof(double)));
        #endif
    }

    fprintf(dump_stack, "}\n");

    PRINT_DIVIDING_DUMP_STACK_STRIP

    fclose(dump_stack);
}

//-----------------------------------------------------------------------------
