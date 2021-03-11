
#include "CPU.h"

//-----------------------------------------------------------------

void assembling_file(const char* file_path, const char* source)  
{
	FILE* txt_file = fopen_file_with_path(file_path, nullptr, source, "rb");
	FILE* obj_file = fopen_file_with_path(file_path, "obj_" , source, "wb");


	text_t file_info(txt_file);
	file_info.txtlib_text_dump();


	char** label_array = (char**) calloc(file_info.num_structs + 1, sizeof(char*));
	assert(label_array);

	int num_of_label = 0;

	for (int indx = 0; indx < file_info.num_structs; indx++) {
		if     (!strncmp(file_info.text[indx].line, "push",  PUSH_SIZE)) {
				fprintf(obj_file, "%d", PUSH_CMD); 

				size_t tmp_indx = PUSH_SIZE;
				while (isspace(file_info.text[indx].line[tmp_indx]))
					tmp_indx++;

				double value = strtod(file_info.text[indx].line + tmp_indx, nullptr);
				//обработка HUGE_VAL and errno

				if (value == 0) {															
					if 	   (!strncmp(file_info.text[indx].line + tmp_indx, "eax", REG_SIZE)) 
							fprintf(obj_file, "%c%c%d%c", REG_MARK,'\n', EAX_REG, '\n'); 			
					else 																		
						if (!strncmp(file_info.text[indx].line + tmp_indx, "ebx", REG_SIZE))	
							fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', EBX_REG, '\n');			
					else 																	
						if (!strncmp(file_info.text[indx].line + tmp_indx, "ecx", REG_SIZE))	
							fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', ECX_REG, '\n');			
					else 																		
						if (!strncmp(file_info.text[indx].line + tmp_indx, "edx", REG_SIZE))	
							fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', EDX_REG, '\n');			
					else																		
						if (!strncmp(file_info.text[indx].line + tmp_indx, "in", IN_SIZE)) {
							scanf("%lg", &value);											
							fprintf(obj_file, "%c%c%lg%c", NUM_MARK, '\n', value, '\n');
						}																		
					else																		
						fprintf(obj_file, "%c%c%lg%c", NUM_MARK, '\n', value, '\n');			
				}																				
				else																			
					fprintf(obj_file, "%c%c%lg%c", NUM_MARK, '\n', value, '\n');				
					// разлиие между 0 и регистром												
			}
		else
			if (!strncmp(file_info.text[indx].line, "pop",  	POP_SIZE)) {
				fprintf(obj_file, "%d", POP_CMD);

				size_t tmp_indx = POP_SIZE;
				while (isspace(file_info.text[indx].line[tmp_indx]))
					tmp_indx++;
															
				if 	   (!strncmp(file_info.text[indx].line + tmp_indx, "eax", REG_SIZE)) 
						fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', EAX_REG, '\n'); 			
				else 																		
					if (!strncmp(file_info.text[indx].line + tmp_indx, "ebx", REG_SIZE))	
						fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', EBX_REG, '\n');			
				else 																		
					if (!strncmp(file_info.text[indx].line + tmp_indx, "ecx", REG_SIZE))	
						fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', ECX_REG, '\n');			
				else 																		
					if (!strncmp(file_info.text[indx].line + tmp_indx, "edx", REG_SIZE))	
						fprintf(obj_file, "%c%c%d%c", REG_MARK, '\n', EDX_REG, '\n');				
				else
					fprintf(obj_file, "%c", '\n');																		
					//pop_error					
			}
		else 
			if (!strncmp(file_info.text[indx].line, "out",   OUT_SIZE)) {
				fprintf(obj_file, "%d%c", OUT_CMD,   '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "add",   ADD_SIZE)) {
				fprintf(obj_file, "%d%c", ADD_CMD,   '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "sub",   SUB_SIZE)) {
				fprintf(obj_file, "%d%c", SUB_CMD,   '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "mul",   MUL_SIZE)) {
				fprintf(obj_file, "%d%c", MUL_CMD,   '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "div",   DIV_SIZE)) {
				fprintf(obj_file, "%d%c", DIV_CMD,   '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "fsqrt", FSQRT_SIZE)) {
				fprintf(obj_file, "%d%c", FSQRT_CMD, '\n');
			}
		else 
			if (!strncmp(file_info.text[indx].line, "in",    IN_SIZE)) {
				fprintf(obj_file, "%d%c", IN_CMD,    '\n');
			}
		else
			if (!strncmp(file_info.text[indx].line, "hlt",   HLT_SIZE)) {
				fprintf(obj_file, "%d%c", HLT_CMD,   '\n');
			}
		else
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
			// else неправильная команда 
	}

	free(label_array);

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


