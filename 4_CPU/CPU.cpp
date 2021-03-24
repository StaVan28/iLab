
#include "CPU.h"

//-----------------------------------------------------------------

void CPU_construct(CPU_t* CPU, const char* file_path, const char* obj_source) 
{
	//errors

	FILE* obj_file = fopen_file_with_path(file_path, nullptr, obj_source, "rb");

	int num_symbols = text_t::txtlib_number_of_symbols_file(obj_file);

    CPU->buffer_cmd = (char*) calloc(num_symbols, sizeof(char));
    assert(CPU->buffer_cmd);

    fread(CPU->buffer_cmd, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);

    for (int indx = 0; indx < NUM_OF_REGS; indx++) 
    	CPU->regs[indx] = POISON_DOUBLE_CPU;

	stack_construct(&(CPU->stack_CPU), "stack_CPU", START_CAPACITY);
}

//-----------------------------------------------------------------

void CPU_destruct(CPU_t* CPU) 
{
	//errors
	//Есть ли смысл всё заливать ядом, ведь всё это доп работа для проца?

	CPU->IP = POISON_INT_CPU;

	free(CPU->buffer_cmd);
	CPU->buffer_cmd = nullptr;	

    for (int indx = 0; indx < NUM_OF_REGS; indx++) 
    	CPU->regs[indx] = POISON_DOUBLE_CPU;

	stack_destruct(&(CPU->stack_CPU));
}

//-----------------------------------------------------------------

void CPU_accomplishment(CPU_t* CPU) 
{
	//errors

	//check assemling in assembler

	register double value       = 0;
	register double addit_value = 0;
	register int 	int_value   = 0;


	while (true) {

		int_value = POINTER_ON_(CPU->buffer_cmd, CPU->IP, char);

		if (int_value == HLT_CMD || int_value == END_CMD)
			break;

		switch(int_value) {
			case PUSH_CMD: 	CPU->IP += sizeof(char); 

							value = POINTER_ON_(CPU->buffer_cmd, CPU->IP, double);
							stack_push(&(CPU->stack_CPU), value);

							CPU->IP += sizeof(double);
						   	break;

			case PUSHR_CMD:	CPU->IP += sizeof(char);

							int_value = POINTER_ON_(CPU->buffer_cmd, CPU->IP, char);
							
							switch(int_value) {												 
								case RAX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RAX_PLACE]);
												CPU->IP += sizeof(char);
												break;

								case RBX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RBX_PLACE]);
												CPU->IP += sizeof(char);
												break;

								case RCX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RCX_PLACE]);
												CPU->IP += sizeof(char);
												break;

								case RDX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RDX_PLACE]);
												CPU->IP += sizeof(char);
												break;
							}
							//проверка регистр

						   	break;

			case POP_CMD:	stack_pop(&(CPU->stack_CPU));

							CPU->IP += sizeof(char);
							break;

			case POPR_CMD:	CPU->IP += sizeof(char);

							value     = stack_pop(&(CPU->stack_CPU));
							int_value = POINTER_ON_(CPU->buffer_cmd, CPU->IP, char);

							switch(int_value) {
								case RAX_REG:	CPU->regs[RAX_PLACE] = value;
												CPU->IP += sizeof(char);
												break;
								
								case RBX_REG:	CPU->regs[RBX_PLACE] = value;
												CPU->IP += sizeof(char);
												break;												
									
								case RCX_REG:	CPU->regs[RCX_PLACE] = value;
												CPU->IP += sizeof(char);
												break;
								
								case RDX_REG:	CPU->regs[RDX_PLACE] = value;
												CPU->IP += sizeof(char);
												break;
							}
							//проверка на ошибки

						   	break;

			case OUT_CMD:	value = stack_pop(&(CPU->stack_CPU));
							printf("%lg\n", value);

						   	CPU->IP += sizeof(char);
						   	break;

			case ADD_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value + addit_value);

						   	CPU->IP += sizeof(char);
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value - addit_value);

						    CPU->IP += sizeof(char);
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value * addit_value);

						   	CPU->IP += sizeof(char);
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value / addit_value);
							//проверка деления на 0;

						   	CPU->IP += sizeof(char);
						   	break;

			case FSQRT_CMD: value = stack_pop(&(CPU->stack_CPU));
							//check negative sqrt

						   	stack_push(&(CPU->stack_CPU), sqrt(value));

						   	CPU->IP += sizeof(char);
						   	return;
						   	break;

			case JMP_CMD:	CPU->IP += sizeof(char); 

							CPU->IP = POINTER_ON_(CPU->buffer_cmd, CPU->IP, int);
							break;
		
			case NOP_CMD:	CPU->IP += sizeof(char);
							break;

			default:
							// error command 
							printf("default\n");
							CPU->IP += sizeof(char);
							break;								
		} 
	}
}

//-----------------------------------------------------------------

void CPU_dump(CPU_t* CPU)
{
	FILE* listning_CPU = fopen("./txt/dump_CPU.txt", "ab");
    assert(listning_CPU);

    fprintf(listning_CPU, "\n******************************************************\n\n");

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

    fprintf(listning_CPU, "\nPointer on regs [%p[]n", CPU->regs);

  	int indx = 0;
    for ( ; indx < stck->cur_size; indx++)
        fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
    for ( ; indx < stck->capacity; indx++)
        fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));

    fprintf(listning_CPU, "Pointer on stack      = %p\n\n", &(CPU->stack_CPU));
    
	//////////////////////
	
	fprintf(dump_stack, "\nData [%p]\n", stck->data);

    if (stck->capacity != POISON_INT_STACK) {
        #ifdef DEFENCE_STACK
            fprintf(dump_stack, " {canary_left} : %d  [%p]\n\n", *(int*)(stck->data - 1 * sizeof(int)), (int*)(stck->data - 1 * sizeof(int)));
        #endif

        int indx = 0;
        for ( ; indx < stck->cur_size; indx++)
            fprintf(dump_stack, "*{%2d} : %lg\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));
        for ( ; indx < stck->capacity; indx++)
            fprintf(dump_stack, " {%2d} : %lg (POISON)\n", indx + 1, *(double*)(stck->data + indx * sizeof(double)));

        #ifdef DEFENCE_STACK
            fprintf(dump_stack, "\n {canary_right} : %d  [%p]\n", *(int*)(stck->data + stck->capacity * sizeof(double)), (int*)(stck->data + stck->capacity * sizeof(double)));
        #endif
    }


	fprintf(listning_CPU, "For see stack please call stack dump\n\n");

    fprintf(listning_CPU, "\n******************************************************\n");

	fclose(listning_CPU);

}