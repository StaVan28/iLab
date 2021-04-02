
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
//#include <TXLib.h>

//-----------------------------------------------------------------------------

#define DEFENCE_STACK 

//!

#define RECREATE_DUMP_STACK_FILE                                \
        FILE* dump_stack = fopen("./txt/dump_stack.txt", "wb"); \
        fclose(dump_stack);                                     \

//!

#define STACK_CONSTRUCT(name, capacity)          \
        my_stack_t name = {};                    \
        stack_construct(&name, #name, capacity); \

//!

#define PRINT_DIVIDING_DUMP_STACK_STRIP                                                    \
        fprintf(dump_stack, "\n******************************************************\n"); \

//!

#define ASSERT_STACK_OK(retrn)        \
        if (stack_error(stck) != 0) { \
                ERROR_INFO            \
                retrn                 \
        }                             \

//!

#define ERROR_INFO                         \
        strcpy(error_info.file, __FILE__); \
        strcpy(error_info.func, __func__); \
        error_info.line = __LINE__;        \

//-----------------------------------------------------------------------------

static const int CHAR_MEMORY  = 25;
static const int CAPACITY_MIN = 4;
static const int CAPACITY_DIF = 4;
static const int TWO_CANARIES = 2;
static const int HAVE_ERROR   = 0;

static const int    POISON_INT_STACK    = 0X1CD7E30B;
static const double POISON_DOUBLE_STACK = NAN;

static const int CANARY_LEFT_STACK  = 0X237CA57A;
static const int CANARY_RIGHT_STACK = 0X2CD71868;
static const int CANARY_LEFT_DATA   = 0X3425D763;
static const int CANARY_RIGHT_DATA  = 0X37B6B0FE;

//-----------------------------------------------------------------------------

struct my_stack_t {
    int   canary_left_stack  = 0;
    char* data               = nullptr;
    char  name[CHAR_MEMORY]  = {};
    int   capacity           = 0;
    int   cur_size           = 0;
    int   hash_              = 0;
    int   error              = 0;
    int   canary_right_stack = 0;
};

//-----------------------------------------------------------------------------

struct error_stack_t {
    char file[CHAR_MEMORY] = {};
    char func[CHAR_MEMORY] = {};
    int  line              = POISON_INT_STACK;
};

//-----------------------------------------------------------------------------

enum {
    SUCCESS                  = 0,
    NULL_PTR_STACK           = 1,
    NEGATIVE_CURRENT_SIZE    = 2,
    NEGATIVE_CAPACITY        = 3,
    CUR_SIZE_MORE_CAPACITY   = 4,
    NULL_PTR_DATA            = 5,
    UNKNOW_NUMBER_CONSTRUCT  = 6,
    UNKNOWN_NUMBER           = 7,
    CANARY_DATA_ERROR        = 8,
    CANARY_STACK_ERROR       = 9,
    HASH_ERROR               = 10,
    REALLOC_ERROR            = 11,
    CALLOC_ERROR             = 12,
    CONSTRUCT_ERROR          = 13,
};

//-----------------------------------------------------------------------------

void   stack_construct(my_stack_t *stck, const char* name, int capacity);

void   stack_destruct(my_stack_t *stck);

void   stack_push(my_stack_t *stck, double data);

double stack_pop(my_stack_t *stck);

void   stack_dump(my_stack_t *stck);

int stack_realloc(my_stack_t *stck);

int stack_hash(my_stack_t* stck);

int stack_error(my_stack_t *stck);

const char* stack_text_error(my_stack_t *stck);

//-----------------------------------------------------------------------------

#endif // STACK_H_INCLUDED
