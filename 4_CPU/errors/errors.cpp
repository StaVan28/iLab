
#include "CPU.h"

//-----------------------------------------------------------------

void CPU::dump(void)
{
	FILE* dump_CPU = fopen("./txt/dump_CPU.txt", "ab");
    assert(dump_CPU);

    fprintf(dump_CPU, "\n******************************************************\n");

    fprintf(dump_CPU, "		CPU:\n\n");

    fprintf(dump_CPU, "CPU (OK) [%p] \n\n", this);

    fprintf(dump_CPU, "IP = %d\n", IP_);

    fprintf(dump_CPU, "\nEBP(buffer_cmd) [%p]\n", EBP_);

    fprintf(dump_CPU, "\nRegs\n");

    FPRINTF_REG(EAX_, "eax");
    FPRINTF_REG(EBX_, "ebx");
    FPRINTF_REG(ECX_, "ecx");
    FPRINTF_REG(EDX_, "edx");

    fprintf(dump_CPU, "\nFLAGS:\n");

    fprintf(dump_CPU, " CF PF AF ZF SF OF\n ");
    for (int indx = NUM_OF_FLAGS; indx > 0; --indx)
        fprintf(dump_CPU, " %d ", (FLAGS_ >> indx) & 1);

    fprintf(dump_CPU, "\n\nPointer on stack = [%p]\n", &ESP_);
	fprintf(dump_CPU, "For see stack please call stack dump\n\n");

    fprintf(dump_CPU, "\n******************************************************\n");

	fclose(dump_CPU);

}

//-----------------------------------------------------------------
