
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

    for (int int_value = 0; int_value < NUM_OF_REGS; int_value++) { 
    	CPU->regs[int_value] = POISON_DOUBLE_CPU;
    }

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

	for (int int_value = 0; int_value < NUM_OF_REGS; int_value++)
		CPU->regs[int_value] = POISON_DOUBLE_CPU;

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

	register size_t tmp_double_IP = 0;
	register size_t tmp_char_IP   = 0;
	register size_t tmp_int_IP    = 0;


	while (true) {

		int_value = POINTER_ON_(CPU->buffer_cmd, char);

		if (int_value == HLT_CMD || int_value == END_CMD)
			break;

		switch(int_value) {
			case PUSH_CMD: 	tmp_char_IP++; 

							value = POINTER_ON_(CPU->buffer_cmd, double);
							stack_push(&(CPU->stack_CPU), value);

							tmp_double_IP++;
						   	break;

			case PUSHR_CMD:	tmp_char_IP++;

							int_value = POINTER_ON_(CPU->buffer_cmd, int);
							
							switch(int_value) {												 
								case RAX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RAX_PLACE]);
												tmp_int_IP++;
												break;

								case RBX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RBX_PLACE]);
												tmp_int_IP++;
												break;

								case RCX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RCX_PLACE]);
												tmp_int_IP++;
												break;

								case RDX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[RDX_PLACE]);
												tmp_int_IP++;
												break;
							}
							//проверка регистр

						   	break;

			case POP_CMD:	stack_pop(&(CPU->stack_CPU));

							tmp_char_IP++;
							break;

			case POPR_CMD:	tmp_char_IP++;

							value     = stack_pop(&(CPU->stack_CPU));
							int_value = POINTER_ON_(CPU->buffer_cmd, int);

							switch(int_value) {
								case RAX_REG:	CPU->regs[RAX_PLACE] = value;
												tmp_int_IP++;
												break;
								
								case RBX_REG:	CPU->regs[RBX_PLACE] = value;
												tmp_int_IP++;
												break;												
									
								case RCX_REG:	CPU->regs[RCX_PLACE] = value;
												tmp_int_IP++;
												break;
								
								case RDX_REG:	CPU->regs[RDX_PLACE] = value;
												tmp_int_IP++;
												break;
							}
							//проверка на ошибки

						   	tmp_int_IP++;
						   	break;

			case OUT_CMD:	value = stack_pop(&(CPU->stack_CPU));
							printf("%lg\n", value);

						   	tmp_char_IP++;
						   	break;

			case ADD_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value + addit_value);

						   	tmp_char_IP++;
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value - addit_value);

						    tmp_char_IP++;
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value * addit_value);

						   	tmp_char_IP++;
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value / addit_value);
							//проверка деления на 0;

						   	tmp_char_IP++;
						   	break;

			case FSQRT_CMD: value = stack_pop(&(CPU->stack_CPU));
							//check negative sqrt

						   	stack_push(&(CPU->stack_CPU), sqrt(value));

						   	tmp_char_IP++;
						   	break;

/*			case JMP_CMD:	{
								CPU->IP++; 

						   		int_value = atoi(buffer_CPU.text[CPU->IP].line);
		   								   			
						   		int indx = 0;

						   		while (indx < buffer_CPU.num_structs) {				   								   			

									if (*(buffer_CPU.text[indx].line) == JMP_MARK){

										if (*(buffer_CPU.text[indx].line + 2) == int_value){
											int_value = indx + 2;
											break;
										}
									}

						   			indx++;
						   		}

								CPU->IP = int_value;
								break;
							}*/
		
			case NOP_CMD:	tmp_char_IP++;
							break;

			default:
							// error command 
							printf("default\n");
							tmp_char_IP++;
						   	break;								
		} 
	}
}

//-----------------------------------------------------------------