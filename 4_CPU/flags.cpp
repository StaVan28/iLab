
#include "CPU.h"

//-----------------------------------------------------------------

void CPU::set_CF(void)
{
	if (DR_ > DAR_) {
		SET_FLAG(CF, FLAGS_);
	}
	else {
		CLEAR_FLAG(CF, FLAGS_);
	}
}

//-----------------------------------------------------------------

void CPU::set_ZF(void)
{
	if (!is_different(DR_, DAR_)) {
		SET_FLAG(ZF, FLAGS_);
	}
	else {
		CLEAR_FLAG(ZF, FLAGS_);
	}
}