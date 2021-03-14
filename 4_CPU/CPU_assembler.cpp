
#include "CPU.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
	FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
	FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");


	text_t file_info(txt_file, WORD_PARSING);
	file_info.txtlib_text_dump();


	size_t num_of_char   = file_info.num_words * sizeof(char) + (file_info.num_words - file_info.num_strings) * sizeof(double) + 1 * sizeof(int);
	size_t tmp_char_IP   = 0;
	size_t tmp_double_IP = 0;
	size_t tmp_int_IP    = 0;

	char* buffer_data = (char*) calloc(num_of_char, sizeof(char));
	assert(buffer_data);
	
/*
	char** label_array = (char**) calloc(file_info.num_structs + 1, sizeof(char*));
	assert(label_array);

	int num_of_label = 0;
*/

	for (int indx = 0; indx < file_info.num_words; indx++) {
		if     (!strncmp(file_info.text[indx].line, "push",  PUSH_SIZE)) {;

				indx++;

				double value = strtod(file_info.text[indx].line, nullptr);
				//обработка HUGE_VAL and errno

				if (value == 0) {															
					if 	   (!strncmp(file_info.text[indx].line, "eax", REG_SIZE)) {

							POINTER_ON_(buffer_data, char) = PUSHR_CMD;
							tmp_char_IP++;

							POINTER_ON_(buffer_data, int)  = EAX_REG;
							tmp_int_IP++;
					}
					else 																		
						if (!strncmp(file_info.text[indx].line, "ebx", REG_SIZE)) {	

							POINTER_ON_(buffer_data, char) = PUSHR_CMD;
							tmp_char_IP++;

							POINTER_ON_(buffer_data, int)  = EBX_REG;
							tmp_int_IP++; 
					}
					else 																	
						if (!strncmp(file_info.text[indx].line, "ecx", REG_SIZE)) {

							POINTER_ON_(buffer_data, char) = PUSHR_CMD;
							tmp_char_IP++;

							POINTER_ON_(buffer_data, int)  = ECX_REG; 
							tmp_int_IP++;
					}
					else 																	
						if (!strncmp(file_info.text[indx].line, "edx", REG_SIZE)) {

							POINTER_ON_(buffer_data, char) = PUSHR_CMD;
							tmp_char_IP++;

							POINTER_ON_(buffer_data, int)  = EDX_REG; 	
							tmp_int_IP++;		
					}
					else																		
						if (!strncmp(file_info.text[indx].line, "in", IN_SIZE)) {

							POINTER_ON_(buffer_data, char)   = PUSH_CMD;
							tmp_char_IP++;
							
							double tmp_value = 0;
							scanf("%lg", &tmp_value);

							POINTER_ON_(buffer_data, double) = tmp_value;
							tmp_double_IP++;
						}																		
					else {

						POINTER_ON_(buffer_data, char)   = PUSH_CMD;
						tmp_char_IP++;

						POINTER_ON_(buffer_data, double) = value;
						tmp_double_IP++;
					}		
				}																				
				else {

					POINTER_ON_(buffer_data, char)   = PUSH_CMD;
					tmp_char_IP++;

					POINTER_ON_(buffer_data, double) = value;			
					tmp_double_IP++;

					// разлиие между 0 и регистром
				}										
			}
		else
			if (!strncmp(file_info.text[indx].line, "pop",  POP_SIZE)) {

				indx++;
															
				if 	   (!strncmp(file_info.text[indx].line, "eax", REG_SIZE)) {

						POINTER_ON_(buffer_data, char) = POPR_CMD; 
						tmp_char_IP++;

						POINTER_ON_(buffer_data, int) = EAX_REG;
						tmp_int_IP++;
				}
				else 																		
					if (!strncmp(file_info.text[indx].line, "ebx", REG_SIZE)) {	

						POINTER_ON_(buffer_data, char) = POPR_CMD; 
						tmp_char_IP++;

						POINTER_ON_(buffer_data, int) = EBX_REG;
						tmp_int_IP++;
				}
				else 																	
					if (!strncmp(file_info.text[indx].line, "ecx", REG_SIZE)) {

						POINTER_ON_(buffer_data, char) = POPR_CMD; 
						tmp_char_IP++;

						POINTER_ON_(buffer_data, int) = ECX_REG;
						tmp_int_IP++;
				}
				else 																	
					if (!strncmp(file_info.text[indx].line, "edx", REG_SIZE)) {	

						POINTER_ON_(buffer_data, char) = POPR_CMD; 
						tmp_char_IP++;

						POINTER_ON_(buffer_data, int) = EDX_REG;
						tmp_int_IP++; 			
				}																	
				else {																		
					POINTER_ON_(buffer_data, char) = POP_CMD; 
					tmp_char_IP++;																					
					//pop_error	
				}				
			}
		else 
			if (!strncmp(file_info.text[indx].line, "out",   OUT_SIZE)) {
				POINTER_ON_(buffer_data, char) = OUT_CMD;
				tmp_char_IP++;
			}
		else 
			if (!strncmp(file_info.text[indx].line, "add",   ADD_SIZE)) {
				POINTER_ON_(buffer_data, char) = ADD_CMD;
				tmp_char_IP++;
			}
		else 
			if (!strncmp(file_info.text[indx].line, "sub",   SUB_SIZE)) {
				POINTER_ON_(buffer_data, char) = SUB_CMD;
				tmp_char_IP++;
			}
		else 
			if (!strncmp(file_info.text[indx].line, "mul",   MUL_SIZE)) {
				POINTER_ON_(buffer_data, char) = MUL_CMD;
				tmp_char_IP++;
			}
		else 
			if (!strncmp(file_info.text[indx].line, "div",   DIV_SIZE)) {
				POINTER_ON_(buffer_data, char) = DIV_CMD;
				tmp_char_IP++;
			}
		else 
			if (!strncmp(file_info.text[indx].line, "fsqrt", FSQRT_SIZE)) {
				POINTER_ON_(buffer_data, char) = FSQRT_CMD;
				tmp_char_IP++;
			}
		else
			if (!strncmp(file_info.text[indx].line, "hlt",   HLT_SIZE)) {
				POINTER_ON_(buffer_data, char) = HLT_CMD;
				tmp_char_IP++;
			}
		else
			if (!strncmp(file_info.text[indx].line, "end",   END_SIZE)) {
				POINTER_ON_(buffer_data, char) = END_CMD;
				tmp_char_IP++;
			}
			else 
				POINTER_ON_(buffer_data, char) = 255;
/*		else
			// до конца говнокод, что делать то А?
			if (!strncmp(file_info.text[indx].line, "jmp",   JMP_SIZE)) {
				fprintf(obj_file, "%d%c", JMP_CMD,   '\n');

				//проверка на правильное написание джампа

				size_t tmp_indx_1 = JMP_SIZE;
				while (isspace(file_info.text[indx].line[tmp_indx_1]))
					tmp_indx_1++;

				CHECK_LABELS(tmp_indx_1)
			}
		else 
			// какие нахер 2 вызова strchr? Ту-ту?
			if (strchr(file_info.text[indx].line, JMP_MARK)) {
				fprintf(obj_file, "%c", JMP_MARK);

				size_t tmp_indx = 0;
				while (file_info.text[indx].line[tmp_indx] != JMP_MARK)
					tmp_indx++;

				file_info.text[indx].line[tmp_indx] = '\0'; 

				CHECK_LABELS(0);																						
			}
		else
			if (!strncmp(file_info.text[indx].line, "nop",   NOP_SIZE)) {
				fprintf(obj_file, "%d%c", NOP_CMD,   '\n');
			}
			// else неправильная команда */
	}

	fwrite(buffer_data, sizeof(char), num_of_char, obj_file);

//	free(label_array);

	fclose(txt_file);	
	fclose(obj_file);
}

//-----------------------------------------------------------------

//@ if you use size function don't remember освободить указатель 
char* concat(const char* file_path, const char* tag, const char* source)
{
	assert(file_path);
	assert(source   );

	if (tag == nullptr) {

		size_t len_file_path = strlen(file_path);
		size_t len_source    = strlen(source   );

	    char* result = (char*) calloc(len_file_path           + len_source + 1, sizeof(char));
	    assert(result);
 	
	    memcpy(result                          , file_path, len_file_path    );
	    memcpy(result           + len_file_path, source   , len_source    + 1);    

    	return result;
	}
	else {

		size_t len_file_path = strlen(file_path);
		size_t len_tag       = strlen(tag      );
		size_t len_source    = strlen(source   );

	    char* result = (char*) calloc(len_file_path + len_tag + len_source + 1, sizeof(char));
	    assert(result);

	   	memcpy(result                          , file_path, len_file_path    );
	    memcpy(result + len_file_path          , tag      , len_tag       	 );
	    memcpy(result + len_file_path + len_tag, source   , len_source    + 1);

	    return result;
	}
}

//-----------------------------------------------------------------

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode)
{
	char* all_file_path = concat(file_path, tag, source);

	FILE* file_name = fopen(all_file_path, mode);
	assert(file_name);

	free(all_file_path);

	return file_name;
}