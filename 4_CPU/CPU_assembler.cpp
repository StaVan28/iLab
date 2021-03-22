
#include "CPU.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
	FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
	FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");


	text_t file_info(txt_file, WORD_PARSING);
	file_info.txtlib_text_dump();


	labels table_labels;

	fill_table_labels(&file_info, &table_labels);
	table_labels.labels_dump();

	size_t num_of_char = (file_info.num_strings + 1) * sizeof(char) + (file_info.num_words - file_info.num_strings) * sizeof(double);
	size_t tmp_IP      = 0;

	char* buffer_data = (char*) calloc(num_of_char, sizeof(char));
	assert(buffer_data);

	for (int indx = 0; indx < file_info.num_words; indx++) {
		if     (!strncmp(file_info.text[indx].line, "push",  PUSH_SIZE)) {;

				indx++;

				double value = strtod(file_info.text[indx].line, nullptr);
				//обработка HUGE_VAL and errno

				if (value == 0) {															
					if 	   (!strncmp(file_info.text[indx].line, "rax", REG_SIZE)) {

							// check git set credentials git config

							POINTER_ON_(buffer_data, tmp_IP, char) = PUSHR_CMD;
							tmp_IP += sizeof(char);

							POINTER_ON_(buffer_data, tmp_IP, char)  = RAX_REG;
							tmp_IP += sizeof(char);
					}
					else 																		
						if (!strncmp(file_info.text[indx].line, "rbx", REG_SIZE)) {	

							POINTER_ON_(buffer_data, tmp_IP, char) = PUSHR_CMD;
							tmp_IP += sizeof(char);

							POINTER_ON_(buffer_data, tmp_IP, char)  = RBX_REG;
							tmp_IP += sizeof(char);
					}
					else 																	
						if (!strncmp(file_info.text[indx].line, "rcx", REG_SIZE)) {

							POINTER_ON_(buffer_data, tmp_IP, char) = PUSHR_CMD;
							tmp_IP += sizeof(char);

							POINTER_ON_(buffer_data, tmp_IP, char)  = RCX_REG; 
							tmp_IP += sizeof(char);
					}
					else 																	
						if (!strncmp(file_info.text[indx].line, "rdx", REG_SIZE)) {

							POINTER_ON_(buffer_data, tmp_IP, char) = PUSHR_CMD;
							tmp_IP += sizeof(char);

							POINTER_ON_(buffer_data, tmp_IP, char)  = RDX_REG; 	
							tmp_IP += sizeof(char);		
					}
					else																		
						if (!strncmp(file_info.text[indx].line, "in", IN_SIZE)) {

							POINTER_ON_(buffer_data, tmp_IP, char)   = PUSH_CMD;
							tmp_IP += sizeof(char);
							
							double tmp_value = 0;
							scanf("%lg", &tmp_value);

							POINTER_ON_(buffer_data, tmp_IP, double) = tmp_value;
							tmp_IP += sizeof(double);
						}																		
					else {

						POINTER_ON_(buffer_data, tmp_IP, char)   = PUSH_CMD;
						tmp_IP += sizeof(char);

						POINTER_ON_(buffer_data, tmp_IP, double) = value;
						tmp_IP += sizeof(double);
					}		
				}																				
				else {

					POINTER_ON_(buffer_data, tmp_IP, char)   = PUSH_CMD;
					tmp_IP += sizeof(char);

					POINTER_ON_(buffer_data, tmp_IP, double) = value;			
					tmp_IP += sizeof(double);

					// разлиие между 0 и регистром
				}										
			}
		else
			if (!strncmp(file_info.text[indx].line, "pop",  POP_SIZE)) {
															
				if 	   (!strncmp(file_info.text[indx + NEXT_ELEMENT].line, "rax", REG_SIZE)) {

						POINTER_ON_(buffer_data, tmp_IP, char) = POPR_CMD; 
						tmp_IP += sizeof(char);

						POINTER_ON_(buffer_data, tmp_IP, char) = RAX_REG;
						tmp_IP += sizeof(char);
				}
				else 																		
					if (!strncmp(file_info.text[indx + NEXT_ELEMENT].line, "rbx", REG_SIZE)) {	
						indx++;

						POINTER_ON_(buffer_data, tmp_IP, char) = POPR_CMD; 
						tmp_IP += sizeof(char);

						POINTER_ON_(buffer_data, tmp_IP, char) = RBX_REG;
						tmp_IP += sizeof(char);
				}
				else 																	
					if (!strncmp(file_info.text[indx + NEXT_ELEMENT].line, "rcx", REG_SIZE)) {
						indx++;

						POINTER_ON_(buffer_data, tmp_IP, char) = POPR_CMD; 
						tmp_IP += sizeof(char);

						POINTER_ON_(buffer_data, tmp_IP, char) = RCX_REG;
						tmp_IP += sizeof(char);
				}
				else 																	
					if (!strncmp(file_info.text[indx + NEXT_ELEMENT].line, "rdx", REG_SIZE)) {	
						indx++;

						POINTER_ON_(buffer_data, tmp_IP, char) = POPR_CMD; 
						tmp_IP += sizeof(char);

						POINTER_ON_(buffer_data, tmp_IP, char) = RDX_REG;
						tmp_IP += sizeof(char); 			
				}																	
				else {															
					POINTER_ON_(buffer_data, tmp_IP, char) = POP_CMD; 
					tmp_IP += sizeof(char);																				
					//pop_error	
				}				
			}
		else 
			if (!strncmp(file_info.text[indx].line, "out",   OUT_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = OUT_CMD;
				tmp_IP += sizeof(char);
			}
		else 
			if (!strncmp(file_info.text[indx].line, "add",   ADD_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = ADD_CMD;
				tmp_IP += sizeof(char);
			}
		else 
			if (!strncmp(file_info.text[indx].line, "sub",   SUB_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = SUB_CMD;
				tmp_IP += sizeof(char);
			}
		else 
			if (!strncmp(file_info.text[indx].line, "mul",   MUL_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = MUL_CMD;
				tmp_IP += sizeof(char);
			}
		else 
			if (!strncmp(file_info.text[indx].line, "div",   DIV_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = DIV_CMD;
				tmp_IP += sizeof(char);
			}
		else 
			if (!strncmp(file_info.text[indx].line, "fsqrt", FSQRT_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = FSQRT_CMD;
				tmp_IP += sizeof(char);
			}
		else
			if (!strncmp(file_info.text[indx].line, "hlt",   HLT_SIZE)) { 
				POINTER_ON_(buffer_data, tmp_IP, char) = HLT_CMD;
				tmp_IP += sizeof(char);
			}
		else
			if (!strncmp(file_info.text[indx].line, "end",   END_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = END_CMD;
				tmp_IP += sizeof(char);
			}
		else
			if (!strncmp(file_info.text[indx].line, "jmp",   JMP_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = JMP_CMD;
				tmp_IP += sizeof(char);

				//проверка на правильное написание джампа : (!)
				indx++;

				int position = table_labels.find_label(file_info.text[indx].line);

				POINTER_ON_(buffer_data, tmp_IP, int) = position;

				tmp_IP += sizeof(int);
			}
		else 
			if (strchr(file_info.text[indx].line, MARK_LABEL)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = NOP_CMD;	
				tmp_IP += sizeof(char);	
			}
		else
			if (!strncmp(file_info.text[indx].line, "nop",   NOP_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = NOP_CMD;
				tmp_IP += sizeof(char);
			}
			// else неправильная команда
	}	


	table_labels.labels_dump();

	fwrite(buffer_data, sizeof(char), num_of_char, obj_file);

	free(buffer_data);
	buffer_data = nullptr;

	fclose(txt_file);	
	fclose(obj_file);
}

//-----------------------------------------------------------------

void fill_table_labels(text_t* file_info, labels* table_labels) {

	for (int indx = 0; indx < file_info->num_words; indx++) {

		size_t tmp_IP = 0;

		if     (!strncmp(file_info->text[indx].line, "jmp",   JMP_SIZE)) {
				tmp_IP += sizeof(char);

				//проверка на правильное написание джампа : (!)
				indx++;

				table_labels->check_label_jmp(file_info->text[indx].line, POISON_POSITION);
				tmp_IP += sizeof(int);
			}
		else 
			if (strchr(file_info->text[indx].line, MARK_LABEL)) {

				table_labels->check_label_mark(file_info->text[indx].line, tmp_IP);	
				tmp_IP += sizeof(char);	
			} 
	}

}