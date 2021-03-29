
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

//-----------------------------------------------------------------

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
			indx++;									\
			IP += sizeof(char);						\
		}											\

//-

#define IF_STRCMP_JMP_SCND(str_cmd)													\
		if (!strcmp(file_info->text[indx].line, str_cmd)) {							\
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

void add_CPU_info_in_buf(char* buffer_data, int num_of_bytes);

//-----------------------------------------------------------------

#endif // ASSEMBLER_H_INCLUDED