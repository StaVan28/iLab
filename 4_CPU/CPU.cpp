
#include "CPU.h"

//-----------------------------------------------------------------

CPU::CPU(void) : 
	ESP_("CPU_stack", START_CAPACITY) 
{
	//TODO errors

	RECREATE_DUMP_CPU_FILE

	FILE* obj_file = fopen_file_with_path("./txt/", nullptr, "obj_source", "rb");

	int num_symbols = text_t::txtlib_number_of_symbols_file(obj_file);

    EBP_ = (char*) calloc(num_symbols, sizeof(char));
    assert(EBP_);

    fread(EBP_, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);
}

//-----------------------------------------------------------------

CPU::CPU(const char* file_path, const char* obj_source) :
	ESP_("CPU_stack", START_CAPACITY)
{
	//TODO errors

	RECREATE_DUMP_CPU_FILE

	FILE* obj_file = fopen_file_with_path(file_path, nullptr, obj_source, "rb");

	int num_symbols = text_t::txtlib_number_of_symbols_file(obj_file);

	Stack ESP_("CPU_stack", START_CAPACITY);

    EBP_ = (char*) calloc(num_symbols, sizeof(char));
    assert(EBP_);

    fread(EBP_, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);
}

//-----------------------------------------------------------------

CPU::~CPU(void) 
{
	//TODO errors

	free(EBP_);
	EBP_ = nullptr;	
}

//-----------------------------------------------------------------

void CPU::run(void)
{
	//errors

	//check assemling in assembler

	while (true) {

		IR_ = POINTER_ON_(EBP_, IP_, char);

		if (IR_ == HLT_CMD || IR_ == END_CMD)
			break;

		switch(IR_) {
			case PUSH_CMD: 	IP_ += sizeof(char); 

							DR_ = POINTER_ON_(EBP_, IP_, double);
							ESP_.push(DR_);

							IP_ += sizeof(double);
						   	break;

			case PUSHR_CMD:	IP_ += sizeof(char);

							IR_ = POINTER_ON_(EBP_, IP_, char);
							
							switch(IR_) {												 
								case EAX_REG:	ESP_.push(EAX_);
												IP_ += sizeof(char);
												break;

								case EBX_REG:	ESP_.push(EBX_);
												IP_ += sizeof(char);
												break;

								case ECX_REG:	ESP_.push(ECX_);
												IP_ += sizeof(char);
												break;

								case EDX_REG:	ESP_.push(EDX_);
												IP_ += sizeof(char);
												break;
							}
							//проверка регистр

						   	break;

			case POP_CMD:	ESP_.pop();

							IP_ += sizeof(char);
							break;

			case POPR_CMD:	IP_ += sizeof(char);

							DR_ = ESP_.pop();
							IR_ = POINTER_ON_(EBP_, IP_, char);

							switch(IR_) {
								case EAX_REG:	EAX_ = DR_;
												IP_ += sizeof(char);
												break;
								
								case EBX_REG:	EBX_ = DR_;
												IP_ += sizeof(char);
												break;												
									
								case ECX_REG:	ECX_ = DR_;
												IP_ += sizeof(char);
												break;
								
								case EDX_REG:	EDX_ = DR_;
												IP_ += sizeof(char);
												break;
							}
							//проверка на ошибки

						   	break;

			case IN_CMD:	printf("IN enter: ");
							scanf("%lg", &(DR_));

							ESP_.push(DR_);

						   	IP_ += sizeof(char);
						   	break;

			case OUT_CMD:	DR_ = ESP_.pop();
							printf("%lg\n", DR_);

							ESP_.push(DR_);

						   	IP_ += sizeof(char);
						   	break;
 
			case ADD_CMD:	POP_TWO_VARIABLES(DR_, DAR_, ESP_);

							ESP_.push(DR_ + DAR_);

						   	IP_ += sizeof(char);
						   	break;

			case SUB_CMD:	POP_TWO_VARIABLES(DR_, DAR_, ESP_);

							ESP_.push(DAR_ - DR_);

						    IP_ += sizeof(char);
						   	break;

			case MUL_CMD:	POP_TWO_VARIABLES(DR_, DAR_, ESP_);

							ESP_.push(DR_ * DAR_);

						   	IP_ += sizeof(char);
						   	break;

			case DIV_CMD:	POP_TWO_VARIABLES(DR_, DAR_, ESP_);

							ESP_.push(DAR_ / DR_);

						   	IP_ += sizeof(char);
						   	break;

			case FSQRT_CMD: DR_ = ESP_.pop();

						   	ESP_.push(sqrt(DR_));

						   	IP_ += sizeof(char);
						   	break;

			case CMP_CMD: 	POP_TWO_VARIABLES(DR_, DAR_, ESP_);

							set_CF();
							set_ZF();

							PUSH_TWO_VARIABLES(DR_, DAR_, ESP_);

						   	IP_ += sizeof(char);
						   	break;

			case JMP_CMD:	IP_ += sizeof(char); 

							IP_ = POINTER_ON_(EBP_, IP_, int);
							break;

			case JNE_CMD:	IP_ += sizeof(char);

							if (FLAGS_ & ZF)
								IP_ += sizeof(int);
							else 
								IP_  = POINTER_ON_(EBP_, IP_, int);

							break;

			case JE_CMD:	IP_ += sizeof(char);

							if (FLAGS_ & ZF)
								IP_  = POINTER_ON_(EBP_, IP_, int);
							else 
								IP_ += sizeof(int);

							break;

			case JBE_CMD:	IP_ += sizeof(char); 

							if ((FLAGS_ & ZF) || (FLAGS_ & CF))
								IP_  = POINTER_ON_(EBP_, IP_, int);
							else 
								IP_ += sizeof(int);

							break;

			case JB_CMD:	IP_ += sizeof(char); 

							if ((FLAGS_ & ZF) || (FLAGS_ & CF))
								IP_ += sizeof(int);
							else 
								IP_  = POINTER_ON_(EBP_, IP_, int);

							break;

			case JAE_CMD:	IP_ += sizeof(char); 

							if (FLAGS_ & CF)
								IP_ += sizeof(int);
							else 
								IP_  = POINTER_ON_(EBP_, IP_, int);

							break;

			case JA_CMD:	IP_ += sizeof(char);

							if (FLAGS_ & ZF)
								IP_  = POINTER_ON_(EBP_, IP_, int);
							else 
								IP_ += sizeof(int);

							break;

			case NOP_CMD:	IP_ += sizeof(char);
							break;

			default:
							// error command 
							printf("default command? check buffer\n");
							printf("IP_ = %d\n", IP_);
							return;
							break;								
		} 
	}
}

//-----------------------------------------------------------------