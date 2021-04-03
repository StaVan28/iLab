
#ifndef CPU_H_INCLUDED
#define CPU_H_INCLUDED

//-----------------------------------------------------------------------------
	
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "stack.h"
#include "txtlib.h"
#include "labels.h"
#include "assembler.h"
#include "settings.h"

//-----------------------------------------------------------------------------

class CPU {

	private:
		// general purpose registers
		double EAX_ = POISON_DOUBLE_CPU;
		double EBX_ = POISON_DOUBLE_CPU;
		double ECX_ = POISON_DOUBLE_CPU;
		double EDX_ = POISON_DOUBLE_CPU;

		// regs for only CPU using
		double DR_  = POISON_DOUBLE_CPU;
		double DAR_ = POISON_DOUBLE_CPU;
		int    IR_  = POISON_INT_CPU;

		// data	segment
		char* EBP_ = nullptr;

		// stack ptr with instraction ptr
		int   IP_  = START_IP;
		Stack ESP_;

		// flag register
		char FLAGS_ = 0;

	   	void set_CF(void);
	   	void set_ZF(void);

	public:

		CPU(void);
		CPU(const char* file_path, const char* obj_source);

	   ~CPU(void);

        CPU(const CPU&)              = delete;
        CPU& operator = (const CPU&) = delete;

	   	void run(void);
	   	void dump(void);
};

//-----------------------------------------------------------------------------

#include "flags.h"
#include "errors.h"

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
};

//-----------------------------------------------------------------------------

enum REGS_CMDS {
	EAX_REG = 32,
	EBX_REG = 33,
	ECX_REG = 34,
	EDX_REG = 35,
};

#endif // CPU_H_INCLUDED