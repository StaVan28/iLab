
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

#include "txtlib.h"
#include "stack.h"
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

#endif // CPU_H_INCLUDED