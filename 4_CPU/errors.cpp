
#include "CPU.h"

//-----------------------------------------------------------------

void CPU_dump(CPU_t* CPU)
{
	FILE* dump_CPU = fopen("./txt/dump_CPU.txt", "ab");
    assert(dump_CPU);

    fprintf(dump_CPU, "\n******************************************************\n");

    fprintf(dump_CPU, "		CPU:\n\n");

    fprintf(dump_CPU, "CPU (OK) [%p] \n\n", &CPU);

    fprintf(dump_CPU, "IP = %d\n", CPU->IP);

    fprintf(dump_CPU, "\nEBP(buffer_cmd) [%p]\n", CPU->EBP);

    CPU_listening(dump_CPU, CPU);

/*  rewrite
    int indx = 0;
    for ( ; indx < stck->cur_size; indx++)
        fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
    for ( ; indx < stck->capacity; indx++)
        fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
*/

    fprintf(dump_CPU, "\nRegs\n");

    FPRINTF_REG(CPU->EAX, "eax");
    FPRINTF_REG(CPU->EBX, "ebx");
    FPRINTF_REG(CPU->ECX, "ecx");
    FPRINTF_REG(CPU->EDX, "edx");

    fprintf(dump_CPU, "\nFLAGS:\n");

    fprintf(dump_CPU, " CF PF AF ZF SF OF\n ");
    for (int indx = NUM_OF_FLAGS; indx > 0; --indx)
        fprintf(dump_CPU, " %d ", (CPU->FLAGS >> indx) & 1);

    fprintf(dump_CPU, "\n\nPointer on stack = [%p]\n", &(CPU->ESP));
	fprintf(dump_CPU, "For see stack please call stack dump\n\n");

    fprintf(dump_CPU, "\n******************************************************\n");

	fclose(dump_CPU);

}

//-----------------------------------------------------------------

void CPU_listening(FILE* listening, CPU_t* CPU)
{
    FILE* obj_file = fopen("./txt/obj_source", "rb");
    assert(obj_file);

    fclose(obj_file);
}
