   
#ifndef TXTLIB_H_INCLUDED
#define TXTLIB_H_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>

//-----------------------------------------------------------------------------

#define PRINT_DIVIDING_DUMP_TEXT_STRIP                                                    \
        fprintf(text_dump, "\n******************************************************\n"); \

//-----------------------------------------------------------------------------

enum modes_text_t {
    STRING_PARSING = 1,
      WORD_PARSING = 2,
};

//-----------------------------------------------------------------------------

struct line_t { 
    int   real_num = 0;
    int   length   = 0;
    char* line     = nullptr;
};

//-----------------------------------------------------------------------------

class text_t {

    int mode = 0;

    public:

    char*   buffer_data     = nullptr;
    line_t* text            = nullptr;     

    int     num_strings     = 0;
    int     num_structs     = 0;
    int     num_symbols     = 0;
    int     num_words       = 0;
    
    text_t(char* buffer, const int mode);
    text_t(FILE* source, const int mode);

    ~text_t(void);

    static int txtlib_number_of_symbols_file(FILE* source);

    static int txtlib_number_of_symbols_buff(char* buffer);

    static int txtlib_number_of_strings(char* buffer);

    static int txtlib_number_of_words(char* buffer);

    void txtlib_fill_line_t_string(void);

    void txtlib_fill_line_t_word(void);

    void txtlib_text_dump(void);


};

//-----------------------------------------------------------------------------

#endif // TXTLIB_H_INCLUDED
