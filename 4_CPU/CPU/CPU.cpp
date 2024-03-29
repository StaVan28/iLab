
#include "CPU.h"

//-----------------------------------------------------------------

CPU::CPU(void) : 
    ESP_("CPU_stack", START_CAPACITY) 
{
    RECREATE_DUMP_CPU_FILE

    FILE* obj_file = fopen_file_with_path("./txt/", nullptr, "obj_source", "rb");

    int num_symbols = Text::txtlib_number_of_symbols_file(obj_file);

    EBP_ = (char*) calloc(num_symbols, sizeof(char));
    assert(EBP_);

    fread(EBP_, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);
}

//-----------------------------------------------------------------

CPU::CPU(const char* file_path, const char* obj_source) :
    ESP_("CPU_stack", START_CAPACITY)
{
    RECREATE_DUMP_CPU_FILE

    FILE* obj_file = fopen_file_with_path(file_path, nullptr, obj_source, "rb");

    int num_symbols = Text::txtlib_number_of_symbols_file(obj_file);

    EBP_ = (char*) calloc(num_symbols, sizeof(char));
    assert(EBP_);

    fread(EBP_, sizeof(char), num_symbols, obj_file);

    fclose(obj_file);
}

//-----------------------------------------------------------------

CPU::~CPU(void) 
{
    free(EBP_);
    EBP_ = nullptr;    
}

//-----------------------------------------------------------------

void CPU::run(void)
{
    while (true) {

        IR_ = POINTER_ON_(EBP_, IP_, char);

        if (IR_ == HLT_CMD || IR_ == END_CMD)
            break;

        switch(IR_) 
        {
            case PUSHC_CMD:   IP_ += sizeof(char); 

                              DR_ = POINTER_ON_(EBP_, IP_, double);
                              ESP_.push(DR_);

                              IP_ += sizeof(double);
                              break;

            case PUSHR_CMD:   IP_ += sizeof(char);

                              IR_ = POINTER_ON_(EBP_, IP_, char);
                            
                              switch(IR_) 
                              {                                                 
                                  PUSH_REGISTERS(EAX_)                                                 
                                  PUSH_REGISTERS(EBX_)                                                 
                                  PUSH_REGISTERS(ECX_)                                                 
                                  PUSH_REGISTERS(EDX_)
                              }

                              break;

            case PUSHOC_CMD:  IP_ += sizeof(char);

                              IR_ = POINTER_ON_(EBP_, IP_, int);

                              IP_ += sizeof(int);
                              break;

            case PUSHOR_CMD:  IP_ += sizeof(char);

                              IR_  = POINTER_ON_(EBP_, IP_, char);

                              IP_ += sizeof(char);
                              break;

            case PUSHORC_CMD: IP_ += sizeof(char);

                              IR_  = POINTER_ON_(EBP_, IP_, int);
                              IP_ += sizeof(int);

                              IR_  = POINTER_ON_(EBP_, IP_, int);
                              IP_ += sizeof(int);

                              break;

            case POP_CMD:     IP_ += sizeof(char);

                              ESP_.pop();
                              break;

            case POPR_CMD:    IP_ += sizeof(char);

                              DR_ = ESP_.pop();
                              IR_ = POINTER_ON_(EBP_, IP_, char);

                              switch(IR_) 
                              {
                                  POP_REGISTERS(EAX_)
                                  POP_REGISTERS(EBX_)
                                  POP_REGISTERS(ECX_)
                                  POP_REGISTERS(EDX_)
                              }

                              break;

            case POPOC_CMD:   IP_ += sizeof(char);

                              IR_ = POINTER_ON_(EBP_, IP_, int);

                              IP_ += sizeof(int);
                              break;

            case POPOR_CMD:   IP_ += sizeof(char);

                              IR_ = POINTER_ON_(EBP_, IP_, char);

                              IP_ += sizeof(char);
                              break;

            case POPORC_CMD:  IP_ += sizeof(char);

                              IR_  = POINTER_ON_(EBP_, IP_, int);
                              IP_ += sizeof(int);

                              IR_  = POINTER_ON_(EBP_, IP_, int);
                              IP_ += sizeof(int);

                              break;

            case IN_CMD:      IP_ += sizeof(char);

                              printf("IN enter: ");
                              scanf("%lg", &(DR_));

                              ESP_.push(DR_);

                              break;

            case OUT_CMD:     IP_ += sizeof(char);

                              DR_ = ESP_.pop();
                              printf("%lg\n", DR_);

                              ESP_.push(DR_);

                              break;

            case CMP_CMD:     IP_ += sizeof(char);

                              POP_TWO_VARIABLES(IR_, IAR_, ESP_);

                              set_CF();
                              set_ZF();

                              PUSH_TWO_VARIABLES(IR_, IAR_, ESP_);

                              break;
 
            case ADD_CMD:     BINARY_OPERATION_CPU(+)

            case SUB_CMD:     BINARY_OPERATION_CPU(-)

            case MUL_CMD:     BINARY_OPERATION_CPU(*)

            case DIV_CMD:     BINARY_OPERATION_CPU(/)

            case FSQRT_CMD:   UNARY_OPERATION_CPU(sqrt)

            case SIN_CMD:     UNARY_OPERATION_CPU(sin)

            case COS_CMD:     UNARY_OPERATION_CPU(cos)

            case NEG_CMD:     UNARY_OPERATION_CPU(-)

            case JMP_CMD:     JUMPS_COMMANDS_CPU(true)

            case JE_CMD:      JUMPS_COMMANDS_CPU(  FLAGS_ & ZF )    

            case JNE_CMD:     JUMPS_COMMANDS_CPU(!(FLAGS_ & ZF))                                    

            case JB_CMD:      JUMPS_COMMANDS_CPU( (FLAGS_ & CF))

            case JAE_CMD:     JUMPS_COMMANDS_CPU(!(FLAGS_ & CF))

            case JBE_CMD:     JUMPS_COMMANDS_CPU(  (FLAGS_ & ZF) || (FLAGS_ & CF))

            case JA_CMD:      JUMPS_COMMANDS_CPU(!((FLAGS_ & ZF) || (FLAGS_ & CF)))

            case NOP_CMD:     IP_ += sizeof(char);
                              break;

            default:          printf("default command? check buffer\n");
                              break;                                
        } 
    }
}

//-----------------------------------------------------------------
