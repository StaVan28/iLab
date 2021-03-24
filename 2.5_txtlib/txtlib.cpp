
#include "txtlib.h"

//-----------------------------------------------------------------------------

text_t::text_t(char* buffer, const int mode) {

    assert(buffer);

    num_symbols = txtlib_number_of_symbols_buff(buffer);

    buffer_data = (char*) calloc(num_symbols + 1, sizeof(char));
    assert(buffer_data);

    strncpy(buffer_data, buffer, num_symbols); 

    num_strings = txtlib_number_of_strings(buffer_data);

    num_words   = txtlib_number_of_words(buffer_data);

    if     (mode == STRING_PARSING) {
            text = (line_t*) calloc(num_strings, sizeof(line_t));
            assert(text);

            txtlib_fill_line_t_string();
    }
    else
        if (mode == WORD_PARSING) {
            text = (line_t*) calloc(num_words, sizeof(line_t));
            assert(text);

            txtlib_fill_line_t_word();
    }
}

//-----------------------------------------------------------------------------

text_t::text_t(FILE* source, const int mode) {

    assert(source);

    num_symbols = txtlib_number_of_symbols_file(source);

    buffer_data = (char*) calloc(num_symbols + 1, sizeof(char));
    assert(buffer_data);

    fread(buffer_data, sizeof(char), num_symbols, source);

    num_strings = txtlib_number_of_strings(buffer_data);

    num_words   = txtlib_number_of_words(buffer_data);

    if     (mode == STRING_PARSING) {
            text = (line_t*) calloc(num_strings, sizeof(line_t));
            assert(text);

            txtlib_fill_line_t_string();
    }
    else
        if (mode == WORD_PARSING) {
            text = (line_t*) calloc(num_words, sizeof(line_t));
            assert(text);

            txtlib_fill_line_t_word();
    }
}

//-----------------------------------------------------------------------------

text_t::~text_t(void) {

    free(buffer_data);

    free(text);
}

//-----------------------------------------------------------------------------

int text_t::txtlib_number_of_symbols_file(FILE* source) {

    assert(source);

    int start_value = ftell(source);
    fseek(source, 0, SEEK_END);

    int tmp_num_symbols = ftell(source);
    fseek(source, start_value, SEEK_SET);

    return tmp_num_symbols;
}

//-----------------------------------------------------------------------------

int text_t::txtlib_number_of_symbols_buff(char* buffer) {

    assert(buffer);

    char* length = nullptr;
    
    length = strchr(buffer, '\0');
    assert(length);
      
    return length - buffer;
}

//-----------------------------------------------------------------------------

int text_t::txtlib_number_of_strings(char* buffer) {

    assert(buffer);

    int tmp_num_strings = 0;

    for (int tmp_indx = 0; buffer[tmp_indx] != '\0'; tmp_indx++) {

        while (isspace(buffer[tmp_indx])) {

            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }

        if (buffer[tmp_indx] != '\0')
            tmp_num_strings++;

        while (buffer[tmp_indx] != '\n') {
            
            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }

        if (buffer[tmp_indx] == '\0')
            break;
    }

    return tmp_num_strings;
}

//-----------------------------------------------------------------------------

int text_t::txtlib_number_of_words(char* buffer) {

    assert(buffer);

    int tmp_num_word = 0;
    int tmp_indx     = 0;

    while (buffer[tmp_indx] != '\0') {

        while (isspace(buffer[tmp_indx]))
            tmp_indx++;

        if (buffer[tmp_indx] != '\0')
            tmp_num_word++;

        while (!isspace(buffer[tmp_indx])) {

            if (buffer[tmp_indx] == '\0')
                break;

            tmp_indx++;
        }
    }

    return tmp_num_word;
}

//-----------------------------------------------------------------------------

void text_t::txtlib_fill_line_t_string(void) {

    int real_line = 0;
    int indx      = 0;

    while (num_structs < num_strings) {

        while (isspace(buffer_data[indx]) || buffer_data[indx] == '\0') {

            if (buffer_data[indx] == '\n')
                real_line++;

            indx++;
        }

        text[num_structs].line = &(buffer_data[indx]);

        while (buffer_data[indx] != '\n') {

            if (buffer_data[indx] == '\0') {

                text[num_structs].real_num = real_line;

                int tmp_indx = indx - 1;
                while (isspace(buffer_data[tmp_indx]))
                    tmp_indx--;

                text[num_structs].length = &(buffer_data[tmp_indx]) - text[num_structs].line + 1;

                if (indx == num_symbols)
                    num_structs++;

                return;
            }

            indx++;
        }

        real_line++;

        int tmp2_indx = indx - 1;
        while (isspace(buffer_data[tmp2_indx]))
            tmp2_indx--;

        buffer_data[tmp2_indx + 1] = '\0';

        text[num_structs].length = &(buffer_data[tmp2_indx]) - text[num_structs].line + 1;

        text[num_structs].real_num = real_line;

        num_structs++;
    }
}

//-----------------------------------------------------------------------------

void text_t::txtlib_fill_line_t_word(void) {
    
    int real_line = 0;
    int tmp_indx  = 0;
    int indx      = 0;

    while (num_structs < num_words) {

        while (isspace(buffer_data[indx]) || buffer_data[indx] == '\0') {

            if (buffer_data[indx] == '\n')
                real_line++;

            indx++;
        }

        text[num_structs].line = &(buffer_data[indx]);

        while (!isspace(buffer_data[indx])) {

            if (buffer_data[indx] == '\0') {

                text[num_structs].real_num = real_line;

                tmp_indx = indx - 1;
                while (isspace(buffer_data[tmp_indx]))
                    tmp_indx--;

                text[num_structs].length = &(buffer_data[tmp_indx]) - text[num_structs].line + 1;

                if (indx == num_symbols)
                    num_structs++;

                return;
            }

            indx++;
        }

        real_line++;

        tmp_indx = indx - 1;
        while (isspace(buffer_data[tmp_indx]))
            tmp_indx--;

        buffer_data[tmp_indx + 1] = '\0';

        text[num_structs].length = &(buffer_data[tmp_indx]) - text[num_structs].line + 1;

        text[num_structs].real_num = real_line;

        num_structs++;
    }
}

//-----------------------------------------------------------------------------

void text_t::txtlib_text_dump(void) {

    FILE* text_dump = fopen("./txt/dump_text.txt", "wb");
    assert(text_dump);

    PRINT_DIVIDING_DUMP_TEXT_STRIP

    fprintf(text_dump, "        TEXT:\n\n");

    fprintf(text_dump, "Pointer buffer of data: %p\n"  , buffer_data);
    fprintf(text_dump, "Pointer line_t structs: %p\n\n", text);

    fprintf(text_dump, "Number of strings = %d\n", num_strings);
    fprintf(text_dump, "Number of structs = %d\n", num_structs);
    fprintf(text_dump, "Number of symbols = %d\n", num_symbols);
    fprintf(text_dump, "Number of words   = %d\n", num_words);

    fprintf(text_dump, "\n[Number in structs]{Real number}(Length)\n\n");

    for (int indx = 0; indx < num_structs; indx++) {

        fprintf(text_dump, "[%3.d]", indx + 1);
        fprintf(text_dump, "{%3.d}", text[indx].real_num);
        fprintf(text_dump, "(%3.d)", text[indx].length);

        fprintf(text_dump,"%s\n", text[indx].line);
    }

    fprintf(text_dump, "\n\nNote! The actual length of the lines is 1 more \n\tdue to the '\\n' and '\\0' characters.\n");

    PRINT_DIVIDING_DUMP_TEXT_STRIP

    fclose(text_dump);
}

//-----------------------------------------------------------------------------
