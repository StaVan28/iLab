   
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
    WORD_PARSING   = 2,
};

//-----------------------------------------------------------------------------

struct line_t { 
    int   real_num_ = 0;
    int   length_   = 0;
    char* line_     = nullptr;
};

//-----------------------------------------------------------------------------

class text_t {

    private:

        int mode = 0;

    public:

        char*   buffer_data_    = nullptr;
        line_t* text_           = nullptr;     

        int     num_strings_    = 0;
        int     num_structs_    = 0;
        int     num_symbols_    = 0;
        int     num_words_      = 0;
        
        text_t(char* buffer, const int mode);
        text_t(FILE* source, const int mode);

        ~text_t();

        text_t(const text_t&)              = delete;
        text_t& operator = (const text_t&) = delete; 

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
