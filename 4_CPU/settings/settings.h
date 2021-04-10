
#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED


//-----------------------------------------------------------------------------

#define POP_TWO_VARIABLES(value_1, value_2, stack)	\
		value_1  = stack.pop();						\
		value_2  = stack.pop();						\

//-

#define PUSH_TWO_VARIABLES(value_1, value_2, stack)	\
		stack.push(value_2);						\
		stack.push(value_1);						\

//-

#define POINTER_ON_(ptr_data, IP, format)	\
		*(format*)(ptr_data + IP)			\

//-----------------------------------------------------------------------------

static const long long int CPU_UNIQUE_NUMBER = 0x75E7348131; 

static const int START_IP = sizeof(long long int) + sizeof(int);

static const int    POISON_INT_CPU    = 0x7F3428BE;
static const double POISON_DOUBLE_CPU = NAN;
static const int    START_CAPACITY    = 4;

static const double EPSILON = 1e-6;

static const int NEXT_ELEMENT = 1;
static const int ERROR        = 0;

//-----------------------------------------------------------------------------

enum CPU_CMDS {
	PUSH_CMD  = 1,
	OUT_CMD   = 2,
	ADD_CMD   = 3,
	SUB_CMD   = 4,
	MUL_CMD   = 5,
	DIV_CMD   = 6,
	FSQRT_CMD = 7,
	IN_CMD    = 8,
	POP_CMD   = 9,
	HLT_CMD   = 10,
	NOP_CMD   = 11,
	JMP_CMD   = 12,
	END_CMD   = 13,
	PUSHR_CMD = 14,
	POPR_CMD  = 15,
	CMP_CMD   = 16,
	JNE_CMD   = 17,
	JE_CMD    = 18,
	JBE_CMD   = 19,
	JB_CMD    = 20,
	JAE_CMD   = 21,
	JA_CMD    = 22,
	SIN_CMD   = 23,
	COS_CMD   = 24,
	NEG_CMD   = 25,
};

//-----------------------------------------------------------------------------

enum REGS_CMDS {
	EAX_REG = 32,
	EBX_REG = 33,
	ECX_REG = 34,
	EDX_REG = 35,
};

//-----------------------------------------------------------------------------

char* concat(const char* str1, const char* str2, const char* str3);

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode);

double is_different(double value_1, double value_2);

//-----------------------------------------------------------------

#endif // SETTINGS_H_INCLUDED