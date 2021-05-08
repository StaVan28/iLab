
#ifndef AKINATOR_TEXT_HPP_INCLUDED
#define AKINATOR_TEXT_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <locale.h>
#include <ctype.h>

//-----------------------------------------------------------------------------

const int EMPTY_FILE = 0;

//-----------------------------------------------------------------------------

class AkinatorText
{
    private:

        std::size_t num_symbols_ = 0;
        char*       buffer_data_ = 0;

        std::size_t num_symbols_in_file(FILE* base_file) const noexcept;

    public:

        AkinatorText();
        AkinatorText(const std::string base_path);
       ~AkinatorText();

       std::size_t num_symbols() const noexcept;
       char*       buffer_data() const noexcept;
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_TEXT_HPP_INCLUDED