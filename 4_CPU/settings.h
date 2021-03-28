
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED


//-----------------------------------------------------------------------------

#define POP_TWO_VARIABLES					\
		CPU->DR  = stack_pop(&(CPU->ESP));	\
		CPU->DAR   = stack_pop(&(CPU->ESP));	\

//-

#define POINTER_ON_(ptr_data, IP, format)	\
		*(format*)(ptr_data + IP)			\

//-----------------------------------------------------------------------------


static const int    POISON_INT_CPU    = 0x7F3428BE;
static const double POISON_DOUBLE_CPU = NAN;
static const int    START_CAPACITY    = 8;

static const double EPSILON = 1e-6;

static const int NEXT_ELEMENT = 1;
static const int ERROR        = 0;

//-----------------------------------------------------------------------------

char* concat(const char* str1, const char* str2, const char* str3);

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode);

double is_different(double value_1, double value_2);

//-----------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED