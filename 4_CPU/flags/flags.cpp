
#include "CPU.h"

//-----------------------------------------------------------------

void CPU::set_CF(void)
{
	if (IR_ < IAR_) {
		printf("set CF\n");
		printf("FLAGS_ before = %c\n", FLAGS_);
		SET_FLAG(CF, FLAGS_);
		printf("FLAGS_ after  = %c\n", FLAGS_);
	}
	else {
		CLEAR_FLAG(CF, FLAGS_);
	}
}

//-----------------------------------------------------------------

void CPU::set_ZF(void)
{
	if (IR_ == IAR_) {
		printf("set ZF\n");
		printf("FLAGS_ before = %c\n", FLAGS_);
		SET_FLAG(ZF, FLAGS_);
		printf("FLAGS_ after  = %c\n", FLAGS_);
	}
	else {
		CLEAR_FLAG(ZF, FLAGS_);
	}
}