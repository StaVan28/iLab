
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED


//-----------------------------------------------------------------------------

#define POP_TWO_VARIABLES							\
		value       = stack_pop(&(CPU->stack_CPU));	\
		addit_value = stack_pop(&(CPU->stack_CPU));	\

//-

#define POINTER_ON_(ptr_data, IP, format)	\
		*(format*)(ptr_data + IP)			\

//-----------------------------------------------------------------------------

static const int NUM_OF_REGS = 4;

static const int    POISON_INT_CPU    = 0x7F3428BE;
static const double POISON_DOUBLE_CPU = NAN;
static const int    START_CAPACITY    = 8;

static const int NEXT_ELEMENT = 1;
static const int ERROR        = 0;

//------------------------------------------------------------------------------

enum CMDS_SIZE {
	PUSH_SIZE     = 4,
	OBJ_PUSH_SIZE = 1,
	OUT_SIZE      = 3,
	ADD_SIZE      = 3,
	SUB_SIZE      = 3,
	MUL_SIZE      = 3,
	DIV_SIZE      = 3,
	FSQRT_SIZE    = 5,
	IN_SIZE       = 2,
	POP_SIZE      = 3,
	OBJ_POP_SIZE  = 1,
	HLT_SIZE      = 3,
	REG_SIZE      = 3,
	NOP_SIZE      = 3,
	JMP_SIZE      = 3,
	END_SIZE      = 3,
	CMP_SIZE      = 3,
};

//-----------------------------------------------------------------------------

enum PLACE_REGS {
	RAX_PLACE = 0,
	RBX_PLACE = 1,
	RCX_PLACE = 2,
	RDX_PLACE = 3,
};

//-----------------------------------------------------------------------------

char* concat(const char* str1, const char* str2, const char* str3);

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode);

//-----------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED