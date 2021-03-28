
#include "CPU.h"

//-----------------------------------------------------------------

inline void set_CF(CPU_t* CPU)
{
	if (CPU->DR > CPU->DAR) {
		SET_FLAG(CF, CPU->FLAGS);
	}
	else {
		CLEAR_FLAG(CF, CPU->FLAGS);
	}
}

//-----------------------------------------------------------------

inline void set_ZF(CPU_t* CPU)
{
	if (!is_different(CPU->DR, CPU->DAR)) {
		SET_FLAG(ZF, CPU->FLAGS);
	}
	else {
		CLEAR_FLAG(ZF, CPU->FLAGS);
	}
}