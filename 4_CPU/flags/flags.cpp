
#include "CPU.h"

//-----------------------------------------------------------------

void CPU::set_CF(void)
{
	if (IR_ < IAR_) {
		SET_FLAG(CF, FLAGS_);
	}
	else {
		CLEAR_FLAG(CF, FLAGS_);
	}
}

//-----------------------------------------------------------------

void CPU::set_ZF(void)
{
	if (IR_ == IAR_) {
		SET_FLAG(ZF, FLAGS_);
	}
	else {
		CLEAR_FLAG(ZF, FLAGS_);
	}
}