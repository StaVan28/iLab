   
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

enum TextMode {
    STRING_PARSING   = 1,
    WORD_PARSING     = 2,
    AKINATOR_PARSING = 3,
};

//-----------------------------------------------------------------------------

struct line_t { 
    int   real_num_ = 0;
    int   length_   = 0;
    char* line_     = nullptr;
};

//-----------------------------------------------------------------------------

class Text {

    private:

        int mode_ = 0;

        char*   buffer_data_ = nullptr;
        line_t* text_        = nullptr;     

        int num_strings_ = 0;
        int num_structs_ = 0;
        int num_symbols_ = 0;
        int num_words_   = 0;
        int num_lexeme_  = 0;

        void txtlib_fill_line_t_string();
        void txtlib_fill_line_t_word  ();

        void choose_parsing(const TextMode mode);

    public:
        
        Text(char* buffer, const TextMode mode);
        Text(FILE* source, const TextMode mode);

       ~Text();

        Text(const Text&)              = delete;
        Text& operator = (const Text&) = delete; 

        static int txtlib_number_of_symbols_file(FILE* source);
        static int txtlib_number_of_symbols_buff(char* buffer);
        static int txtlib_number_of_strings     (char* buffer);
        static int txtlib_number_of_words       (char* buffer);

        const char* cur_mode   () const noexcept;
              int   num_strings() const noexcept;
              int   num_symbols() const noexcept;
              int   num_words  () const noexcept; 

        void txtlib_text_dump() const noexcept;
};

//-----------------------------------------------------------------------------

#endif // TXTLIB_H_INCLUDED
