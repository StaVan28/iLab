
#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

//-----------------------------------------------------------------------------
	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "stack.h"
#include "txtlib.h"

//-----------------------------------------------------------------------------

#define POP_TWO_VARIABLES							\
		value       = stack_pop(&(CPU->stack_CPU));	\
		addit_value = stack_pop(&(CPU->stack_CPU));	\

//-

#define CHECK_LABELS(start_of_reading)																\
		do {																						\
			for (int tmp_indx = 0; tmp_indx <= num_of_label; tmp_indx++) {							\
																									\
				if (tmp_indx == num_of_label) {														\
					label_array[tmp_indx] = file_info.text[indx].line + start_of_reading;			\
																									\
					fprintf(obj_file, "%d%c", tmp_indx, '\n');										\
					num_of_label++;																	\
																									\
					break;																			\
				}																					\
				if (!strcmp(file_info.text[indx].line + start_of_reading, label_array[tmp_indx])) {	\
																									\
					fprintf(obj_file, "%d%c", tmp_indx, '\n');										\
					num_of_label++;																	\
																									\
					break;																			\
				}																					\
			}																						\
		} while(0);																					\

//-----------------------------------------------------------------------------

static const int NUM_OF_REGS = 4;

static const char REG_MARK = '~';
static const char NUM_MARK = '_';
static const char JMP_MARK = ':';

static const int    POISON_INT_CPU    = 0x7F3428BE;
static const double POISON_DOUBLE_CPU = NAN;
static const int    START_CAPACITY    = 4;

static const int NEXT_ELEMENT = 1;
static const int ERROR        = 0;

//-----------------------------------------------------------------------------

struct CPU_t {

	int    IP                = 0;
	char*  buffer_cmd 	     = 0; 
	double regs[NUM_OF_REGS] = {};

	my_stack_t stack_CPU = {};
};

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
};

//-----------------------------------------------------------------------------

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
};

//-----------------------------------------------------------------------------

enum REGS {
	EAX_REG = 32,
	EBX_REG = 33,
	ECX_REG = 34,
	EDX_REG = 35,
};

//-----------------------------------------------------------------------------

enum PLACE_REGS {
	EAX_PLACE = 0,
	EBX_PLACE = 1,
	ECX_PLACE = 2,
	EDX_PLACE = 3,
};

//-----------------------------------------------------------------------------

void CPU_construct(CPU_t* CPU, const char* file_path = "./txt/", const char* obj_source = "obj_source");

void CPU_destruct(CPU_t* CPU);

void CPU_accomplishment(CPU_t* CPU); 

void assembling_file(const char* file_path = "./txt/", const char* source = "source"); 

char* concat(const char* str1, const char* str2, const char* str3);

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode);

#endif // CPU_H_INCLUDED