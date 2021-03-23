
#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

//-----------------------------------------------------------------

static const int FIRST_PASS  = 0;
static const int SECOND_PASS = 1;
static const int NUM_OF_PASS	 = 2;

//-----------------------------------------------------------------

void assembling_file(const char* file_path = "./txt/", const char* source = "source");

void fill_table_labels(text_t* file_info, labels* table_labels);

//-----------------------------------------------------------------

#endif // ASSEMBLER_H_INCLUDED