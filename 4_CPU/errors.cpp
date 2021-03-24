
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

    fprintf(listning_CPU, "\nBuffer_cmd [%p]\n",   CPU->buffer_cmd);
/*  rewrite
    int indx = 0;
    for ( ; indx < stck->cur_size; indx++)
        fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
    for ( ; indx < stck->capacity; indx++)
        fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
*/

    fprintf(listning_CPU, "\nPointer on regs [%p]\n", CPU->regs);

    for (int indx = 0; indx < NUM_OF_REGS; indx++) {

    	if (CPU->regs[indx] != POISON_DOUBLE_STACK)
    		fprintf(listning_CPU, " {");
    	else	
    		fprintf(listning_CPU, "*{");

    	switch(indx) {
    		FPRINTF_REG(listning_CPU, RAX_REG, "rax");
    		FPRINTF_REG(listning_CPU, RBX_REG, "rbx");
    		FPRINTF_REG(listning_CPU, RCX_REG, "rcx");
    		FPRINTF_REG(listning_CPU, RDX_REG, "rdx");
    	}
    	
    	if (CPU->regs[indx] != POISON_DOUBLE_STACK)
    		fprintf(listning_CPU, "} : %lg (POISON)\n", CPU->regs[indx]);
    	else	
    		fprintf(listning_CPU, "} : %lg\n"         , CPU->regs[indx]);
    }


    fprintf(listning_CPU, "\nPointer on stack = [%p]\n", &(CPU->stack_CPU));
	fprintf(listning_CPU, "For see stack please call stack dump\n\n");

    fprintf(listning_CPU, "\n******************************************************\n");

	fclose(listning_CPU);

}

//-----------------------------------------------------------------
