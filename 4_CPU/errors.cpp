
#include "CPU.h"

//-----------------------------------------------------------------

void CPU_dump(CPU_t* CPU)
{
	FILE* listning_CPU = fopen("./txt/dump_CPU.txt", "ab");
    assert(listning_CPU);

    fprintf(listning_CPU, "\n******************************************************\n");

    fprintf(listning_CPU, "		CPU:\n\n");

    fprintf(listning_CPU, "CPU (OK) [%p] \n\n", &CPU);

    fprintf(listning_CPU, "IP = %d\n", CPU->IP);

    fprintf(listning_CPU, "\nEBP(buffer_cmd) [%p]\n", CPU->EBP);

/*  rewrite
    int indx = 0;
    for ( ; indx < stck->cur_size; indx++)
        fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
    for ( ; indx < stck->capacity; indx++)
        fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
*/

    fprintf(listning_CPU, "\nRegs\n");

    FPRINTF_REG(EAX, "eax");
    FPRINTF_REG(EBX, "ebx");
    FPRINTF_REG(ECX, "ecx");
    FPRINTF_REG(EDX, "edx");

    fprintf(listning_CPU, "\nPointer on stack = [%p]\n", &(CPU->ESP));
	fprintf(listning_CPU, "For see stack please call stack dump\n\n");

    fprintf(listning_CPU, "\n******************************************************\n");

	fclose(listning_CPU);

}

//-----------------------------------------------------------------
