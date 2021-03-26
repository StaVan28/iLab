
#include "CPU.h"

//-----------------------------------------------------------------

void CPU_construct(CPU_t* CPU, const char* file_path, const char* obj_source) 
{
	//errors

	RECREATE_DUMP_CPU_FILE

	FILE* obj_file = fopen_file_with_path(file_path, nullptr, obj_source, "rb");

	int num_symbols = text_t::txtlib_number_of_symbols_file(obj_file);

    CPU->EBP = (char*) calloc(num_symbols, sizeof(char));
    assert(CPU->EBP);

    fread(CPU->EBP, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);

	stack_construct(&(CPU->ESP), "stack_CPU", START_CAPACITY);
}

//-----------------------------------------------------------------

void CPU_destruct(CPU_t* CPU) 
{
	//errors
	//Есть ли смысл всё заливать ядом, ведь всё это доп работа для проца?

	free(CPU->EBP);
	CPU->EBP = nullptr;	

	stack_destruct(&(CPU->ESP));
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

		int_value = POINTER_ON_(CPU->EBP, CPU->IP, char);

		if (int_value == HLT_CMD || int_value == END_CMD)
			break;

		switch(int_value) {
			case PUSH_CMD: 	CPU->IP += sizeof(char); 

							value = POINTER_ON_(CPU->EBP, CPU->IP, double);
							stack_push(&(CPU->ESP), value);

							CPU->IP += sizeof(double);
						   	break;

			case PUSHR_CMD:	CPU->IP += sizeof(char);

							int_value = POINTER_ON_(CPU->EBP, CPU->IP, char);
							
							switch(int_value) {												 
								case EAX_REG:	stack_push(&(CPU->ESP), CPU->EAX);
												CPU->IP += sizeof(char);
												break;

								case EBX_REG:	stack_push(&(CPU->ESP), CPU->EBX);
												CPU->IP += sizeof(char);
												break;

								case ECX_REG:	stack_push(&(CPU->ESP), CPU->ECX);
												CPU->IP += sizeof(char);
												break;

								case EDX_REG:	stack_push(&(CPU->ESP), CPU->EDX);
												CPU->IP += sizeof(char);
												break;
							}
							//проверка регистр

						   	break;

			case POP_CMD:	stack_pop(&(CPU->ESP));

							CPU->IP += sizeof(char);
							break;

			case POPR_CMD:	CPU->IP += sizeof(char);

							value     = stack_pop(&(CPU->ESP));
							int_value = POINTER_ON_(CPU->EBP, CPU->IP, char);

							switch(int_value) {
								case EAX_REG:	CPU->EAX = value;
												CPU->IP += sizeof(char);
												break;
								
								case EBX_REG:	CPU->EBX = value;
												CPU->IP += sizeof(char);
												break;												
									
								case ECX_REG:	CPU->ECX = value;
												CPU->IP += sizeof(char);
												break;
								
								case EDX_REG:	CPU->EDX = value;
												CPU->IP += sizeof(char);
												break;
							}
							//проверка на ошибки

						   	break;

			case OUT_CMD:	value = stack_pop(&(CPU->ESP));
							printf("%lg\n", value);

						   	CPU->IP += sizeof(char);
						   	break;

			case ADD_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->ESP), value + addit_value);

						   	CPU->IP += sizeof(char);
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->ESP), value - addit_value);

						    CPU->IP += sizeof(char);
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->ESP), value * addit_value);

						   	CPU->IP += sizeof(char);
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->ESP), value / addit_value);
							//проверка деления на 0;

						   	CPU->IP += sizeof(char);
						   	break;

			case FSQRT_CMD: value = stack_pop(&(CPU->ESP));
							//check negative sqrt

						   	stack_push(&(CPU->ESP), sqrt(value));

						   	CPU->IP += sizeof(char);
						   	break;

			case JMP_CMD:	CPU->IP += sizeof(char); 

							CPU->IP = POINTER_ON_(CPU->EBP, CPU->IP, int);
							break;
		
			case NOP_CMD:	CPU->IP += sizeof(char);
							break;

			default:
							// error command 
							printf("default coomand? check buffer\n");
							CPU->IP += sizeof(char);
							break;								
		} 
	}
}

//-----------------------------------------------------------------