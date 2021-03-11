
#include "CPU.h"

//-----------------------------------------------------------------

//void.operate(struct.CPU*.cpu,.FILE*.commads){
	//здесьможномпользоваьтекстовуюбиблиотекудляпарсингакоманд
	//возвращаешьмассивстрокспомощьюлибы
	//
//}

void CPU_construct(CPU_t* CPU, const char* file_path, const char* obj_source) 
{
	//errors

	FILE* obj_file = fopen_file_with_path(file_path, nullptr, obj_source, "rb");

	int num_symbols = text_t::txtlib_number_of_symbols_file(obj_file);

    CPU->buffer_cmd = (char*) calloc(num_symbols + 1, sizeof(char));
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

	register size_t cmd_num     = 0;
	register double value       = 0;
	register double addit_value = 0;
	register int    int_value   = 0;

	text_t buffer_CPU(CPU->buffer_cmd);

	while (CPU->IP < buffer_CPU.num_structs) {

		cmd_num = atoi(buffer_CPU.text[CPU->IP].line);

		if (cmd_num == ERROR) {
			CPU->IP++;
			break;
		}


		if (cmd_num == HLT_CMD)
			break;
		//error

		switch(cmd_num) {
			case PUSH_CMD: 	if (*(buffer_CPU.text[CPU->IP].line + OBJ_PUSH_SIZE) == NUM_MARK) {

									CPU->IP++; 

							   		value = atof(buffer_CPU.text[CPU->IP].line);
							   		stack_push(&(CPU->stack_CPU), value);
							}
							else 
								if (*(buffer_CPU.text[CPU->IP].line + OBJ_PUSH_SIZE) == REG_MARK) {

									CPU->IP++; 

							   		int_value = atoi(buffer_CPU.text[CPU->IP].line);
							   		
							   		switch(int_value) {												 
										case EAX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[EAX_PLACE]);
														break;

										case EBX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[EBX_PLACE]);
														break;

										case ECX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[ECX_PLACE]);
														break;

										case EDX_REG:	stack_push(&(CPU->stack_CPU), CPU->regs[EDX_PLACE]);
														break;
									}
							   		//проверка регистр
							}
/*							else
								error push;*/

						   	CPU->IP++;
						   	break;

			case POP_CMD:	value = stack_pop(&(CPU->stack_CPU));


							if (*(buffer_CPU.text[CPU->IP].line + NEXT_ELEMENT) == REG_MARK){

								CPU->IP++;

								int_value = atoi(buffer_CPU.text[CPU->IP].line);

								switch(int_value) {
									case EAX_REG:	CPU->regs[EAX_PLACE] = value;
													break;
									
									case EBX_REG:	CPU->regs[EBX_PLACE] = value;
													break;												
										
									case ECX_REG:	CPU->regs[ECX_PLACE] = value;
													break;
									
									case EDX_REG:	CPU->regs[EDX_PLACE] = value;
													break;
								}
							}	
							//проверка на ошибки

						   	CPU->IP++;
						   	break;

			case OUT_CMD:	value = stack_pop(&(CPU->stack_CPU));
							printf("%lg\n", value);

						   	CPU->IP++;
						   	break;

			case ADD_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value + addit_value);

						   	CPU->IP++;
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value - addit_value);

						   	CPU->IP++;
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value * addit_value);

						   	CPU->IP++;
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES;

							stack_push(&(CPU->stack_CPU), value / addit_value);
							//проверка деления на 0;

						   	CPU->IP++;
						   	break;

			case FSQRT_CMD: value = stack_pop(&(CPU->stack_CPU));
							//check negative sqrt

						   	stack_push(&(CPU->stack_CPU), sqrt(value));

						   	CPU->IP++;
						   	break;

			case JMP_CMD:	{
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
							}
		
			case NOP_CMD:	CPU->IP++;
							break;

			default:
							// error command 
							printf("default\n");
							CPU->IP++;
						   	break;								
		} 
	}
}

//-----------------------------------------------------------------