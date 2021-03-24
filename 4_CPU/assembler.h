
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

//-----------------------------------------------------------------

void assembling_file(const char* file_path = "./txt/", const char* source = "source");

void frst_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data);

void scnd_pass_of_assembler(text_t* file_info, labels* table_labels, char** buffer_data);

//-----------------------------------------------------------------

#endif // ASSEMBLER_H_INCLUDED