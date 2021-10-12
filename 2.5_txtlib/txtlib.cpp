
#include "txtlib.h"

//-----------------------------------------------------------------------------

Text::Text(char* buffer, const TextMode mode) :
    mode_ {mode}
{
    assert(this);
    assert(buffer);

    num_symbols_ = txtlib_number_of_symbols_buff(buffer);

    buffer_data_ = (char*) calloc(num_symbols_ + 1, sizeof(char));
    assert(buffer_data_);

    strncpy(buffer_data_, buffer, num_symbols_); 

    num_strings_ = txtlib_number_of_strings(buffer_data_);
    num_words_   = txtlib_number_of_words  (buffer_data_);

    choose_parsing(mode);
}

//-----------------------------------------------------------------------------

Text::Text(FILE* source, const TextMode mode) :
    mode_ {mode} 
{
    assert(this);
    assert(source);

    num_symbols_ = txtlib_number_of_symbols_file(source);

    buffer_data_ = (char*) calloc(num_symbols_ + 1, sizeof(char));
    assert(buffer_data_);

    fread(buffer_data_, sizeof(char), num_symbols_, source);

    num_strings_ = txtlib_number_of_strings(buffer_data_);
    num_words_   = txtlib_number_of_words  (buffer_data_);

    choose_parsing(mode);
}

//-----------------------------------------------------------------------------

void Text::choose_parsing(const TextMode mode)
{
    if (mode == STRING_PARSING) 
    {
        num_lexeme_ = num_strings_;

        text_ = (line_t*) calloc(num_lexeme_, sizeof(line_t));
        assert(text_);

        parsing_text(string_comparator, num_lexeme_);
    }

    if (mode == WORD_PARSING) 
    {
        num_lexeme_ = num_words_;

        text_ = (line_t*) calloc(num_lexeme_, sizeof(line_t));
        assert(text_);

        parsing_text(word_comparator, num_lexeme_);
    }
}

//-----------------------------------------------------------------------------

Text::~Text() 
{
    assert(this);

    free(buffer_data_);

    free(text_);
}

//-----------------------------------------------------------------------------

int Text::txtlib_number_of_symbols_file(FILE* source) 
{
    assert(source);

    int start_value = ftell(source);
    fseek(source, 0, SEEK_END);

    int tmp_num_symbols_ = ftell(source);
    fseek(source, start_value, SEEK_SET);

    return tmp_num_symbols_;
}

//-----------------------------------------------------------------------------

int Text::txtlib_number_of_symbols_buff(char* buffer) 
{
    assert(buffer);

    char* length_ = nullptr;
    
    length_ = strchr(buffer, '\0');
    assert(length_);
      
    return length_ - buffer;
}

//-----------------------------------------------------------------------------

int Text::txtlib_number_of_strings(char* buffer) 
{
    assert(buffer);

    int tmp_num_strings_ = 0;

    for (int tmp_indx = 0; buffer[tmp_indx] != '\0'; tmp_indx++) 
    {

        while (isspace(buffer[tmp_indx])) 
        {

            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }

        if (buffer[tmp_indx] != '\0')
            tmp_num_strings_++;

        while (buffer[tmp_indx] != '\n') 
        {
            
            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }

        if (buffer[tmp_indx] == '\0')
            break;
    }

    return tmp_num_strings_;
}

//-----------------------------------------------------------------------------

int Text::txtlib_number_of_words(char* buffer) 
{
    assert(buffer);

    int tmp_num_word = 0;
    int tmp_indx     = 0;

    while (buffer[tmp_indx] != '\0') 
    {

        while (isspace(buffer[tmp_indx]))
            tmp_indx++;

        if (buffer[tmp_indx] != '\0')
            tmp_num_word++;

        while (!isspace(buffer[tmp_indx])) 
        {

            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }
    }

    return tmp_num_word;
}

//-----------------------------------------------------------------------------

void Text::parsing_text(bool (*comparator) (int indx, const char* buffer), int border)
{
    int real_line = 0;
    int tmp_indx  = 0;
    int indx      = 0;

    while (num_structs_ < border) 
    {

        while (isspace(buffer_data_[indx]) || buffer_data_[indx] == '\0') 
        {

            if (buffer_data_[indx] == '\n')
                real_line++;

            indx++;
        }

        text_[num_structs_].line_ = &(buffer_data_[indx]);

        while (comparator(indx, buffer_data_)) 
        {

            if (buffer_data_[indx] == '\0') 
            {

                text_[num_structs_].real_num_ = real_line;

                int tmp_indx = indx - 1;
                while (isspace(buffer_data_[tmp_indx]))
                    tmp_indx--;

                text_[num_structs_].length_ = &(buffer_data_[tmp_indx]) - text_[num_structs_].line_ + 1;

                if (indx == num_symbols_)
                    num_structs_++;

                return;
            }

            indx++;
        }

        real_line++;

        tmp_indx = indx - 1;
        while (isspace(buffer_data_[tmp_indx]))
            tmp_indx--;

        buffer_data_[tmp_indx + 1] = '\0';

        text_[num_structs_].length_   = &(buffer_data_[tmp_indx]) - text_[num_structs_].line_ + 1;
        text_[num_structs_].real_num_ = real_line;

        num_structs_++;
    }
}

//-----------------------------------------------------------------------------

bool string_comparator(int indx, const char* buffer)
{
    return buffer[indx] != '\n';
}

//-----------------------------------------------------------------------------

bool word_comparator(int indx, const char* buffer)
{
    return !isspace(buffer[indx]);
}

//-----------------------------------------------------------------------------

void Text::txtlib_text_dump() const noexcept 
{
    FILE* text_dump = fopen("./txt/dump_text.txt", "wb");
    assert(text_dump);

    PRINT_DIVIDING_DUMP_TEXT_STRIP

    fprintf(text_dump, "            TEXT:\n");
    fprintf(text_dump, "    Current mode: %s\n\n"  , cur_mode());

    fprintf(text_dump, "Pointer buffer of data: %p\n"  , buffer_data_);
    fprintf(text_dump, "Pointer line_t structs: %p\n\n", text_);

    fprintf(text_dump, "Number of strings = %d\n", num_strings_);
    fprintf(text_dump, "Number of structs = %d\n", num_structs_);
    fprintf(text_dump, "Number of symbols = %d\n", num_symbols_);
    fprintf(text_dump, "Number of words   = %d\n", num_words_);
    fprintf(text_dump, "Number of lexemes = %d\n", num_lexeme_);

    fprintf(text_dump, "\n[Number in structs]{Real number}(length_)\n\n");

    for (int indx = 0; indx < num_structs_; indx++) {

        fprintf(text_dump, "[%3.d]", indx + 1);
        fprintf(text_dump, "{%3.d}", text_[indx].real_num_);
        fprintf(text_dump, "(%3.d)", text_[indx].length_);

        fprintf(text_dump,"%s\n", text_[indx].line_);
    }

    fprintf(text_dump, "\n\nNote! The actual length_ of the line_s is 1 more \n\tdue to the '\\n' and '\\0' characters.\n");

    PRINT_DIVIDING_DUMP_TEXT_STRIP

    fclose(text_dump);
}

//-----------------------------------------------------------------------------

const char* Text::cur_mode() const noexcept
{
    switch(mode_)
    {
        case   STRING_PARSING: return   "string mode";
        case     WORD_PARSING: return     "word mode";
        default:               return   "!!!ERROR!!!";
    }
}

//-----------------------------------------------------------------------------
