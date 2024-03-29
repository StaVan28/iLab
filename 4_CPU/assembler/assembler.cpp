
#include "assembler.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
    FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
    FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");

    assert(txt_file);
    assert(obj_file);

    Text file_info(txt_file, WORD_PARSING);
    file_info.txtlib_text_dump();

    Labels table_labels;

    int num_of_bytes = (file_info.num_strings_)                            * sizeof(char)   + \
                       (file_info.num_words_ - file_info.num_strings_) * 2 * sizeof(double) + \
                       START_IP;
 
    char* buffer_data = (char*) calloc(num_of_bytes, sizeof(char));
    assert(buffer_data);

    add_CPU_info_in_buf(buffer_data, num_of_bytes);

    pass_of_assembler(FRST_PASS, &file_info, &table_labels, &buffer_data);
    pass_of_assembler(SCND_PASS, &file_info, &table_labels, &buffer_data);

    table_labels.labels_dump();

    fwrite(buffer_data, sizeof(char), num_of_bytes, obj_file);

    free(buffer_data);
    buffer_data = nullptr;

    fclose(txt_file);    
    fclose(obj_file);
}

//-----------------------------------------------------------------

void pass_of_assembler(int pass_of_asm, Text* file_info, Labels* table_labels, char** buffer_data)
{
    int tmp_IP = START_IP;

    for (int indx = 0; indx < file_info->num_lexeme_; indx++) 
    {
        if (!strcmp(file_info->text_[indx].line_, "push")) 
        {                                                                                                                        
            indx++;

            char tmp_command = PUSH_BASE_MASK;
            
            int  push_IP = tmp_IP;
            tmp_IP += sizeof(char);

            if (!strcmp(file_info->text_[indx].line_, "["))
            {
                indx++;

                tmp_command |= RAM_CMD_MASK;
            }

            PARSING_PUSH;

            if (!strcmp(file_info->text_[indx].line_, "+"))
            {
                indx++;

                PARSING_PUSH;
            }

            if (!strcmp(file_info->text_[indx].line_, "]") && !ram_flag)
            {
                indx++;
            }

            if (pass_of_asm == FRST_PASS) {
                POINTER_ON_(*buffer_data, push_IP, char) = tmp_command; 
            }

            printf("file_info->text_[indx - 1].line_ = %s\n", file_info->text_[indx - 1].line_);
            printf("file_info->text_[indx    ].line_ = %s\n", file_info->text_[indx    ].line_);
            printf("tmp_command = %d\n", tmp_command);

        }     

        else if (!strcmp(file_info->text_[indx].line_, "pop")) 
        {
            indx++;                                                                                            
                                                                                                
            IF_STRCMP_REG(/*POPR_CMD, */EAX_REG, "eax")    
/*
            else IF_STRCMP_REG(POPR_CMD, EBX_REG, "ebx")

            else IF_STRCMP_REG(POPR_CMD, ECX_REG, "ecx")

            else IF_STRCMP_REG(POPR_CMD, EDX_REG, "edx")
*/
            else 
            {                                                                                            
                indx--;                                                                                        
                READING_DATA(POP_CMD, char)                                                                            
            }                                                                                                
        }                                                                                                    

        // one cmd in row
        else IF_STRCMP_ORD(IN_CMD,    "in")

        else IF_STRCMP_ORD(OUT_CMD,   "out")

        else IF_STRCMP_ORD(ADD_CMD,   "add")

        else IF_STRCMP_ORD(SUB_CMD,   "sub")

        else IF_STRCMP_ORD(MUL_CMD,   "mul")

        else IF_STRCMP_ORD(DIV_CMD,   "div")

        else IF_STRCMP_ORD(FSQRT_CMD, "fsqrt")

        else IF_STRCMP_ORD(NOP_CMD,   "nop")

        else IF_STRCMP_ORD(CMP_CMD,   "cmp")

        else IF_STRCMP_ORD(SIN_CMD,   "sin")

        else IF_STRCMP_ORD(COS_CMD,   "cos")

        else IF_STRCMP_ORD(NEG_CMD,   "neg")


        // jmps
        else IF_STRCMP_JMP(JMP_CMD,   "jmp")

        else IF_STRCMP_JMP(JNE_CMD,   "jne")

        else IF_STRCMP_JMP(JE_CMD,    "je")

        else IF_STRCMP_JMP(JBE_CMD,   "jbe")

        else IF_STRCMP_JMP(JB_CMD,    "jb")

        else IF_STRCMP_JMP(JAE_CMD,   "jae")

        else IF_STRCMP_JMP(JA_CMD,    "ja")

        else IF_STRCMP_MRK(MARK_LABEL)                                                                                    
        
        // end
        else IF_STRCMP_ORD(HLT_CMD,   "hlt")

        else IF_STRCMP_ORD(END_CMD,   "end")

        else if (pass_of_asm == SCND_PASS){
            tmp_IP += sizeof(char);
        }
    }    
}

//-----------------------------------------------------------------

void add_CPU_info_in_buf(char* buffer_data, int num_of_bytes)
{
    int tmp_IP = 0;

    POINTER_ON_(buffer_data, tmp_IP, long long int) = CPU_UNIQUE_NUMBER;
    tmp_IP += sizeof(long long int);

    POINTER_ON_(buffer_data, tmp_IP, int) = num_of_bytes;
    tmp_IP += sizeof(int);    
}

//-----------------------------------------------------------------