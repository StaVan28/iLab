
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

//-----------------------------------------------------------------------------

#define DEFENCE_STACK 

//!

#define RECREATE_DUMP_STACK_FILE                                \
        FILE* dump_stack = fopen("./Txt/dump_stack.txt", "wb"); \
        assert(dump_stack);                                     \
        fclose(dump_stack);                                     \

//!

#define PRINT_DIVIDING_DUMP_STACK_STRIP                                                    \
        fprintf(dump_stack, "\n******************************************************\n"); \

//!

#define ASSERT_STACK_OK(retrn)  \
        if (error() != 0) {     \
                ERROR_INFO      \
                retrn           \
        }                       \

//!

#define ERROR_INFO                         \
        strcpy(error_info.file, __FILE__); \
        strcpy(error_info.func, __func__); \
        error_info.line = __LINE__;        \

//-----------------------------------------------------------------------------

static const int CHAR_MEMORY   = 25;
static const int CAPACITY_MIN  = 4;
static const int CAPACITY_DIF  = 4;
static const int TWO_CANARIES  = 2;
static const int HAVE_ERROR    = 0;
static const int DFLT_CAPACITY = 10; 

static const int    POISON_INT_STACK    = 0X1CD7E30B;
static const double POISON_DOUBLE_STACK = NAN;
static const char   POISON_CHAR_STACK   = -1;

static const int CANARY_LEFT_STACK  = 0X237CA57A;
static const int CANARY_RIGHT_STACK = 0X2CD71868;
static const int CANARY_LEFT_DATA   = 0X3425D763;
static const int CANARY_RIGHT_DATA  = 0X37B6B0FE;

//-----------------------------------------------------------------------------

template <typename data_t>
class Stack 
{
    private:
        int   canary_left_stack_  = 0;
        char* data_               = nullptr;
        char  name_[CHAR_MEMORY]  = {};
        int   capacity_           = 0;
        int   cur_size_           = 0;
        int   hash_               = 0;
        int   error_              = 0;
        int   canary_right_stack_ = 0;

        int realloc_data(void);
        int hash(void);

        int         error(void);
        const char* text_error(void);

    public:
        Stack() = delete;

        Stack(const char* name, int capacity);
       ~Stack();

        Stack(const Stack&)              = delete;
        Stack& operator = (const Stack&) = delete;

        void   push(data_t data);
        data_t pop (void);
        void   dump(void);
};

inline void print_elem(FILE* dump_stack,       int    value);
inline void print_elem(FILE* dump_stack,       double value);
inline void print_elem(FILE* dump_stack,       float  value);
inline void print_elem(FILE* dump_stack,       char   value);
inline void print_elem(FILE* dump_stack, const char*  value);

inline int         get_poison(int*);
inline double      get_poison(double*);
inline float       get_poison(float*);
inline char        get_poison(char*);
inline const char* get_poison(const char**);

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

#include        "stack_impl.hpp"
#include "errors_stack_impl.hpp"

//-----------------------------------------------------------------------------

#endif // STACK_H_INCLUDED
