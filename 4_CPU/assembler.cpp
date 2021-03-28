
#include "CPU.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
	FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
	FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");

	text_t file_info(txt_file, WORD_PARSING);
	file_info.txtlib_text_dump();

	labels table_labels;

	size_t num_of_char = (file_info.num_strings) * sizeof(char) + (file_info.num_words - file_info.num_strings) * sizeof(double);
 
	char* buffer_data = (char*) calloc(num_of_char, sizeof(char));
	assert(buffer_data);

	frst_pass_of_assembler(&file_info, &table_labels, &buffer_data);
	scnd_pass_of_assembler(&file_info, &table_labels, &buffer_data);

	table_labels.labels_dump();

	fwrite(buffer_data, sizeof(char), num_of_char, obj_file);

	free(buffer_data);
	buffer_data = nullptr;

	fclose(txt_file);	
	fclose(obj_file);
}

//-----------------------------------------------------------------

void frst_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data)
{
	size_t tmp_IP = 0;

	for (int indx = 0; indx < file_info->num_words; indx++) {

		// regs cmd
		IF_STRCMP_PUSH(PUSH_CMD, "push")
		
		else IF_STRCMP_POP(POP_CMD,   "pop")

		// one cmd in row
		else IF_STRCMP_ORD(OUT_CMD,   "out")

		else IF_STRCMP_ORD(ADD_CMD,   "add")

		else IF_STRCMP_ORD(SUB_CMD,   "sub")

		else IF_STRCMP_ORD(MUL_CMD,   "mul")

		else IF_STRCMP_ORD(DIV_CMD,   "div")

		else IF_STRCMP_ORD(FSQRT_CMD, "fsqrt")

		else IF_STRCMP_ORD(NOP_CMD,   "nop")

		else IF_STRCMP_ORD(CMP_CMD,   "cmp")

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
		// else неправильная команда
	}	
}

//-----------------------------------------------------------------

void scnd_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data)
{
	size_t tmp_IP = 0;

	for (int indx = 0; indx < file_info->num_words; indx++) {
		if (!strcmp(file_info->text[indx].line, "push")) {

			indx++;
			tmp_IP += sizeof(char);

			double value = strtod(file_info->text[indx].line, nullptr);
			//обработка HUGE_VAL and errno

			if (!is_different(value, 0)) {			
				IF_STRCMP_REG_SCND(file_info->text[indx].line, "eax", tmp_IP)		

				else IF_STRCMP_REG_SCND(file_info->text[indx].line, "ebx", tmp_IP)

				else IF_STRCMP_REG_SCND(file_info->text[indx].line, "ecx", tmp_IP)

				else IF_STRCMP_REG_SCND(file_info->text[indx].line, "edx", tmp_IP)

				else IF_STRCMP_IN_SCND(file_info->text[indx].line, "in",  tmp_IP)

				else 
					tmp_IP += sizeof(double);		
			}														
			else 	
				tmp_IP += sizeof(double);
			// разлиие между 0 и регистром							

		}
		else if (!strcmp(file_info->text[indx].line, "pop")) {

			tmp_IP += sizeof(char);

			IF_STRCMP_REG_SCND(file_info->text[indx + NEXT_ELEMENT].line, "eax", tmp_IP)		

			else IF_STRCMP_REG_SCND(file_info->text[indx + NEXT_ELEMENT].line, "ebx", tmp_IP)

			else IF_STRCMP_REG_SCND(file_info->text[indx + NEXT_ELEMENT].line, "ecx", tmp_IP)

			else IF_STRCMP_REG_SCND(file_info->text[indx + NEXT_ELEMENT].line, "edx", tmp_IP)	

		}
		else IF_STRCMP_JMP_SCND("jmp")

		else IF_STRCMP_JMP_SCND("jne")

		else IF_STRCMP_JMP_SCND("je")

		else IF_STRCMP_JMP_SCND("jbe")	

		else IF_STRCMP_JMP_SCND("jb")

		else IF_STRCMP_JMP_SCND("jae")

		else IF_STRCMP_JMP_SCND("ja")

		else 
			tmp_IP += sizeof(char);
		
		// else неправильная команда
	}
}