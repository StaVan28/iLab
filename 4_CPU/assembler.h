
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

//-----------------------------------------------------------------

#define IF_STRCMP_PUSH(cmd, cmd_str)															\
		if (!strcmp(file_info->text[indx].line, cmd_str)) {										\
																								\
			indx++;																				\
																								\
			double value = strtod(file_info->text[indx].line, nullptr);							\
			/*обработка HUGE_VAL and errno*/													\
																								\
			if (!is_different(value, 0)) {														\
					 IF_STRCMP_REG_FRST(file_info->text[indx].line, PUSHR_CMD, EAX_REG, "eax")	\
				else IF_STRCMP_REG_FRST(file_info->text[indx].line, PUSHR_CMD, EBX_REG, "ebx")	\
				else IF_STRCMP_REG_FRST(file_info->text[indx].line, PUSHR_CMD, ECX_REG, "ecx")	\
				else IF_STRCMP_REG_FRST(file_info->text[indx].line, PUSHR_CMD, EDX_REG, "edx")	\
				else IF_STRCMP_IN_FRST(IN_CMD, "in")											\
				else {																			\
					READING_DATA(cmd  , char  )													\
					READING_DATA(value, double)													\
				}																				\
			}																					\
			else {																				\
				READING_DATA(cmd  , char  )														\
				READING_DATA(value, double)														\
				/*разлиие между 0 и регистром*/													\
			}																					\
		}																						\

//-

#define IF_STRCMP_POP(cmd, cmd_str)																			\
		if (!strcmp(file_info->text[indx].line, cmd_str)) {													\
			     IF_STRCMP_REG_FRST(file_info->text[indx + NEXT_ELEMENT].line, POPR_CMD, EAX_REG, "eax")	\
			else IF_STRCMP_REG_FRST(file_info->text[indx + NEXT_ELEMENT].line, POPR_CMD, EBX_REG, "ebx")	\
			else IF_STRCMP_REG_FRST(file_info->text[indx + NEXT_ELEMENT].line, POPR_CMD, ECX_REG, "ecx")	\
			else IF_STRCMP_REG_FRST(file_info->text[indx + NEXT_ELEMENT].line, POPR_CMD, EDX_REG, "edx")	\
			else {																							\
					READING_DATA(cmd, char)																	\
					/*pop_error*/																			\
			}																								\
		}																									\

//-

#define IF_STRCMP_ORD(cmd, cmd_str)							\
		if (!strcmp(file_info->text[indx].line, cmd_str)) {	\
			READING_DATA(cmd, char)							\
		}													\

//-

#define IF_STRCMP_JMP(cmd, cmd_str)																	\
		if (!strcmp(file_info->text[indx].line, cmd_str)) {											\
			READING_DATA(cmd, char)																	\
																									\
			indx++;																					\
			table_labels->check_label(file_info->text[indx].line, POISON_POSITION, FROM_JMP_CMD);	\
			tmp_IP += sizeof(int);																	\
		}																							\

//-

#define IF_STRCMP_MRK(label)																\
		if (strchr(file_info->text[indx].line, MARK_LABEL)) {								\
																							\
			table_labels->check_label(file_info->text[indx].line, tmp_IP, FROM_MARK_LABEL);	\
			READING_DATA(NOP_CMD, char)														\
		}																					\

//-
		
#define READING_DATA(cmd, format)							\
		POINTER_ON_(*buffer_data, tmp_IP, format) = cmd;	\
		tmp_IP += sizeof(format);							\

//-

#define IF_STRCMP_REG_FRST(buffer_cmd, cmd, reg, cmd_str)	\
		if (!strcmp(buffer_cmd, cmd_str)) {					\
			READING_DATA(cmd, char)							\
			READING_DATA(reg, char)							\
		}													\

//-

#define IF_STRCMP_REG_SCND(buffer_cmd, cmd_str, IP)	\
		if (!strcmp(buffer_cmd, cmd_str)) {			\
			IP += sizeof(char);						\
		}											\

//-

#define IF_STRCMP_IN_FRST(cmd, cmd_str)						\
		if (!strcmp(file_info->text[indx].line, cmd_str)) {	\
															\
			READING_DATA(cmd, char)							\
															\
			double tmp_value = 0;							\
			scanf("%lg", &tmp_value);						\
															\
			READING_DATA(tmp_value, double)					\
		}													\

//-

#define IF_STRCMP_IN_SCND(buffer_cmd, cmd_str, IP)	\
		if (!strcmp(buffer_cmd, cmd_str)) {			\
			IP += sizeof(double);					\
		}											\

//-

#define IF_STRCMP_JMP_SCND(str_cmd)													\
		if (!strcmp(file_info->text[indx].line, "jmp")) {							\
			tmp_IP += sizeof(char);													\
																					\
			indx++;																	\
			int position = table_labels->find_label(file_info->text[indx].line);	\
																					\
			POINTER_ON_(*buffer_data, tmp_IP, int) = position;						\
			tmp_IP += sizeof(int);													\
		}																			\

//-


//-----------------------------------------------------------------

void assembling_file(const char* file_path = "./txt/", const char* source = "source");

void frst_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data);

void scnd_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data);

//-----------------------------------------------------------------

#endif // ASSEMBLER_H_INCLUDED