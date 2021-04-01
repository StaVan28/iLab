
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

void CPU_run(CPU_t* CPU) 
{
	//errors

	//check assemling in assembler

	while (true) {

		CPU->IR = POINTER_ON_(CPU->EBP, CPU->IP, char);

		if (CPU->IR == HLT_CMD || CPU->IR == END_CMD)
			break;

		switch(CPU->IR) {
			case PUSH_CMD: 	CPU->IP += sizeof(char); 

							CPU->DR = POINTER_ON_(CPU->EBP, CPU->IP, double);
							stack_push(&(CPU->ESP), CPU->DR);

							CPU->IP += sizeof(double);
						   	break;

			case PUSHR_CMD:	CPU->IP += sizeof(char);

							CPU->IR = POINTER_ON_(CPU->EBP, CPU->IP, char);
							
							switch(CPU->IR) {												 
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

							CPU->DR = stack_pop(&(CPU->ESP));
							CPU->IR = POINTER_ON_(CPU->EBP, CPU->IP, char);

							switch(CPU->IR) {
								case EAX_REG:	CPU->EAX = CPU->DR;
												CPU->IP += sizeof(char);
												break;
								
								case EBX_REG:	CPU->EBX = CPU->DR;
												CPU->IP += sizeof(char);
												break;												
									
								case ECX_REG:	CPU->ECX = CPU->DR;
												CPU->IP += sizeof(char);
												break;
								
								case EDX_REG:	CPU->EDX = CPU->DR;
												CPU->IP += sizeof(char);
												break;
							}
							//проверка на ошибки

						   	break;

			case IN_CMD:	printf("IN CMD: ");
							scanf("%lg", &(CPU->DR));

							stack_push(&(CPU->ESP), CPU->DR);

						   	CPU->IP += sizeof(char);
						   	break;

			case OUT_CMD:	CPU->DR = stack_pop(&(CPU->ESP));
							printf("%lg\n", CPU->DR);

							stack_push(&(CPU->ESP), CPU->DR);

						   	CPU->IP += sizeof(char);
						   	break;
 
			case ADD_CMD:	POP_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

							stack_push(&(CPU->ESP), CPU->DR + CPU->DAR);

						   	CPU->IP += sizeof(char);
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

							stack_push(&(CPU->ESP), CPU->DAR - CPU->DR);

						    CPU->IP += sizeof(char);
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

							stack_push(&(CPU->ESP), CPU->DR * CPU->DAR);

						   	CPU->IP += sizeof(char);
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

							stack_push(&(CPU->ESP), CPU->DAR / CPU->DR);

						   	CPU->IP += sizeof(char);
						   	break;

			case FSQRT_CMD: CPU->DR = stack_pop(&(CPU->ESP));

						   	stack_push(&(CPU->ESP), sqrt(CPU->DR));

						   	CPU->IP += sizeof(char);
						   	break;

			case CMP_CMD: 	POP_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

							set_CF(CPU);
							set_ZF(CPU);

							PUSH_TWO_VARIABLES(CPU->DR, CPU->DAR, CPU->ESP);

						   	CPU->IP += sizeof(char);
						   	break;

			case JMP_CMD:	CPU->IP += sizeof(char); 

							CPU->IP = POINTER_ON_(CPU->EBP, CPU->IP, int);
							break;

			case JNE_CMD:	CPU->IP += sizeof(char);

							if (CPU->FLAGS & ZF)
								CPU->IP += sizeof(int);
							else {
								printf("CPU->IP1 = %d\n", CPU->IP);
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);
								printf("CPU->IP2 = %d\n", CPU->IP);
							}

							break;

			case JE_CMD:	CPU->IP += sizeof(char);

							if (CPU->FLAGS & ZF)
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);
							else 
								CPU->IP += sizeof(int);

							break;

			case JBE_CMD:	CPU->IP += sizeof(char); 

							if ((CPU->FLAGS & ZF) || (CPU->FLAGS & CF))
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);
							else 
								CPU->IP += sizeof(int);

							break;

			case JB_CMD:	CPU->IP += sizeof(char); 

							if ((CPU->FLAGS & ZF) || (CPU->FLAGS & CF))
								CPU->IP += sizeof(int);
							else 
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);

							break;

			case JAE_CMD:	CPU->IP += sizeof(char); 

							if (CPU->FLAGS & CF)
								CPU->IP += sizeof(int);
							else 
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);

							break;

			case JA_CMD:	CPU->IP += sizeof(char);

							if (CPU->FLAGS & ZF)
								CPU->IP  = POINTER_ON_(CPU->EBP, CPU->IP, int);
							else 
								CPU->IP += sizeof(int);

							break;

			case NOP_CMD:	CPU->IP += sizeof(char);
							break;

			default:
							// error command 
							printf("default command? check buffer\n");
							printf("CPU->IP = %d\n", CPU->IP);
							return;
							break;								
		} 
	}
}

//-----------------------------------------------------------------