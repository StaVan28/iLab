
#include "CPU.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
	FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
	FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");


	text_t file_info(txt_file, WORD_PARSING);
	file_info.txtlib_text_dump();


	size_t num_of_char = file_info.num_strings * sizeof(char) + (file_info.num_words - file_info.num_strings) * sizeof(double);
	size_t tmp_IP      = 0;

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
			}
		else 
			if (strchr(file_info.text[indx].line, MARK_LABEL)) {
				tmp_IP += sizeof(char);																		
			}
		else
			if (!strncmp(file_info.text[indx].line, "nop",   NOP_SIZE)) {
				POINTER_ON_(buffer_data, tmp_IP, char) = NOP_CMD;
				tmp_IP += sizeof(char);
			}
			// else неправильная команда
	}

	fwrite(buffer_data, sizeof(char), num_of_char, obj_file);

	free(buffer_data);
	buffer_data = nullptr;

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
	    memcpy(result+ len_file_path           , source   , len_source    + 1);    

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
	all_file_path = nullptr;

	return file_name;
}