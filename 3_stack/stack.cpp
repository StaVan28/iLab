
#include "stack.h"

//-----------------------------------------------------------------------------

static error_stack_t error_info = {};

//-----------------------------------------------------------------------------

void stack_construct(my_stack_t *stck, const char* name, int capacity) {

    RECREATE_DUMP_STACK_FILE

    if (stck->canary_left_stack != 0) {

        stck->error = CONSTRUCT_ERROR;
        ERROR_INFO

        return;
    }

    if (stck == nullptr) {

        stck->error = NULL_PTR_STACK;
        ERROR_INFO

        return;
    }

    if (capacity < 0) {

        stck->error = UNKNOWN_NUMBER;
        ERROR_INFO

        return;
    }

    my_stack_t *temp_stck = stck;

    #ifdef DEFENCE_STACK
        stck->data = (char*) calloc(capacity * sizeof(double) + TWO_CANARIES * sizeof(int), sizeof(char));
    #else
        stck->data = (char*) calloc(capacity * sizeof(double), sizeof(char));
    #endif

    if (stck->data == nullptr) {
        stck = temp_stck;
        stck->error = CALLOC_ERROR;
        ERROR_INFO
        return;
    }

    #ifdef DEFENCE_STACK
        stck->data += sizeof(int);

        *(int*)(stck->data - 1 * sizeof(int))           = CANARY_LEFT_DATA;
        *(int*)(stck->data + capacity * sizeof(double)) = CANARY_RIGHT_DATA;
    #endif

    stck->capacity = capacity;

    for (int indx = 0; indx < stck->capacity; indx++)
        *(double*)(stck->data + indx * sizeof(double)) = POISON_DOUBLE_STACK;

    stck->cur_size = 0;

    strcpy(stck->name, name);

    stck->error = 0;

    #ifdef DEFENCE_STACK
        stck->hash_ = stack_hash(stck);

        stck->canary_left_stack = CANARY_LEFT_STACK;
        stck->canary_right_stack = CANARY_RIGHT_STACK;
    #endif

    ASSERT_STACK_OK({return;})
}

//-----------------------------------------------------------------------------

void stack_push(my_stack_t *stck, double data) {

    ASSERT_STACK_OK({return;})

    if (!isfinite(data)) {

        stck->error = UNKNOWN_NUMBER;
        ERROR_INFO

        return;
    }

    int status_realloc = SUCCESS;

    if (stck->cur_size == stck->capacity || stck->capacity < CAPACITY_MIN)
        status_realloc = stack_realloc(stck);

    if (status_realloc == SUCCESS) {
        *(double*)(stck->data + stck->cur_size * sizeof(double)) = data;
        stck->cur_size++;
    }

    #ifdef DEFENCE_STACK
        stck->hash_ = stack_hash(stck);
    #endif

    ASSERT_STACK_OK({return;})
}

//-----------------------------------------------------------------------------

double stack_pop(my_stack_t *stck) {

    ASSERT_STACK_OK({return POISON_DOUBLE_STACK;})

    int status_realloc = SUCCESS;

    if (stck->capacity > CAPACITY_MIN && stck->cur_size * CAPACITY_DIF < stck->capacity)
        status_realloc = stack_realloc(stck);

    double temp_data = 0;

    if (status_realloc == SUCCESS) {
        stck->cur_size--;
        temp_data = *(double*)(stck->data + stck->cur_size * sizeof(double));
        
        if (stck->cur_size >= 0)
            *(double*)(stck->data + stck->cur_size * sizeof(double)) = POISON_DOUBLE_STACK;
    }

    #ifdef DEFENCE_STACK
        stck->hash_ = stack_hash(stck);
    #endif

    ASSERT_STACK_OK({return POISON_DOUBLE_STACK;})

    return temp_data;
}

//-----------------------------------------------------------------------------

void stack_destruct(my_stack_t *stck) {

    ASSERT_STACK_OK()

    stack_dump(stck);

    stck->canary_left_stack = POISON_INT_STACK;

    for (int indx = 0; indx < stck->capacity; indx++)
        *(double*)(stck->data + indx * sizeof(double)) = POISON_INT_STACK;

    stck->capacity = POISON_INT_STACK;
    stck->cur_size = POISON_INT_STACK;

    #ifdef DEFENCE_STACK
        stck->data -= sizeof(int);
    #endif
    free(stck->data);
    stck->data = nullptr;

    stck->hash_ = POISON_INT_STACK;

    stck->canary_right_stack = POISON_INT_STACK;
}

//-----------------------------------------------------------------------------

int stack_realloc(my_stack_t *stck) {

    ASSERT_STACK_OK({return POISON_INT_STACK;})

    int temp_capacity = stck->capacity;

    if (stck->capacity < CAPACITY_MIN)
        stck->capacity  = CAPACITY_MIN;
    else if (stck->cur_size * CAPACITY_DIF < stck->capacity)
        stck->capacity /= 2;
    else
        stck->capacity *= 2;

    char *temp_stck_data = stck->data;


    #ifdef DEFENCE_STACK
        stck->data -= sizeof(int);
        stck->data = (char*) realloc(stck->data, stck->capacity * sizeof(double) + TWO_CANARIES * sizeof(int));
    #else
        stck->data = (char*) realloc(stck->data, stck->capacity * sizeof(double));
    #endif

    if (stck->data == nullptr) {

        stck->data = temp_stck_data;

        stck->error = REALLOC_ERROR;
        ERROR_INFO

        return REALLOC_ERROR;
    }

    #ifdef DEFENCE_STACK
        stck->data += sizeof(int);
    #endif

    for (int indx = temp_capacity; indx < stck->capacity; indx++)
        *(double*)(stck->data + indx * sizeof(double)) = POISON_DOUBLE_STACK;

    #ifdef DEFENCE_STACK
        *(int*)(stck->data + stck->capacity * sizeof(double)) = CANARY_RIGHT_DATA;
        stck->hash_ = stack_hash(stck);
    #endif

    ASSERT_STACK_OK({return POISON_INT_STACK;})

    return SUCCESS;
}

//-----------------------------------------------------------------------------

int stack_hash(my_stack_t* stck) {

    int hash_ = POISON_INT_STACK;

    for (int indx = 0; indx < stck->cur_size; indx++) {

        hash_ = hash_ + (int)(stck->data[indx * sizeof(double)]);

        if (indx % 2) {
            hash_  |= stck->cur_size;
            hash_ <<= stck->capacity;
            hash_  |= *(stck->name);
        }
        else {
            hash_  |= stck->capacity;
            hash_ <<= stck->cur_size;
            hash_  |= *(stck->name);
        }
    }

    return hash_;
}

//-----------------------------------------------------------------------------

void stack_dump(my_stack_t *stck) {

    #ifdef DEBUG
        printf("call stack_dump to %s\n", stck->name);
    #endif

    FILE* dump_stack = fopen("./txt/dump_stack.txt", "ab");
    assert(dump_stack);

    PRINT_DIVIDING_DUMP_STACK_STRIP

    if (!stck->error)
        fprintf(dump_stack, "Stack (OK) [%p] \"%s\" {\n\n", &stck, stck->name);
    else {
        fprintf(dump_stack, "Stack (ERROR %d : %s) [%p] \"%s\" {\n", stck->error, stack_text_error(stck), &stck, stck->name);
        fprintf(dump_stack, "In File : %s, LINE : %d\n", error_info.file, error_info.line);
        fprintf(dump_stack, "In Function : %s\n\n",    error_info.func);

        printf(             "Stack (ERROR %d : %s) [%p] \"%s\" {\n", stck->error, stack_text_error(stck), &stck, stck->name);
        printf(             "In File : %s, LINE : %d\n", error_info.file, error_info.line);
        printf(             "In Function : %s\n\n",    error_info.func);
    }

    #ifdef DEFENCE_STACK
        fprintf(dump_stack, "Canary left  = %d  [%p]\n", stck->canary_left_stack, &(stck->canary_left_stack));
    #endif
    fprintf(dump_stack, "Current size = %d\n", stck->cur_size);
    fprintf(dump_stack, "Capacity     = %d\n", stck->capacity);
    #ifdef DEFENCE_STACK
        fprintf(dump_stack, "Hash         = %d\n", stck->hash_);
        fprintf(dump_stack, "Canary right = %d  [%p]\n", stck->canary_right_stack, &(stck->canary_right_stack));
    #endif

    fprintf(dump_stack, "\nData [%p]\n", stck->data);

    if (stck->capacity != POISON_INT_STACK) {
        #ifdef DEFENCE_STACK
            fprintf(dump_stack, " {canary_left} : %d  [%p]\n\n", *(int*)(stck->data - 1 * sizeof(int)), (int*)(stck->data - 1 * sizeof(int)));
        #endif

        int indx = 0;
        for ( ; indx < stck->cur_size; indx++)
            fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
        for ( ; indx < stck->capacity; indx++)
            fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));

        #ifdef DEFENCE_STACK
            fprintf(dump_stack, "\n {canary_right} : %d  [%p]\n", *(int*)(stck->data + stck->capacity * sizeof(double)), (int*)(stck->data + stck->capacity * sizeof(double)));
        #endif
    }

    fprintf(dump_stack, "}\n");

    PRINT_DIVIDING_DUMP_STACK_STRIP

    fclose(dump_stack);
}

//-----------------------------------------------------------------------------
