
#ifndef PARSING_TREE_H_INCLUDED
#define PARSING_TREE_H_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

const std::size_t START_NUM_TOKENS = 64;

//!

class BufTokens
{
    private:

        TokenDiff*  buf_tokens_ = nullptr;
        std::size_t num_tokens_ = 0;
        std::size_t length_     = 0;

        bool resize ();

    public:

        BufTokens (std::size_t num_tokens);
       ~BufTokens ();

        TokenDiff&       operator[] (const int indx);
        const TokenDiff& operator[] (const int indx) const;

        bool push (char* buf_data_, std::size_t i_data, TokenType type);

        void dump (const char* path_dump) const;

}; // class BufTokens

//!

class TextDiff
{
    private:

        std::size_t num_symbols_ = 0;
        char*       buf_data_    = nullptr;

        void num_symbols_in_file (FILE* diff_base);
        void create_buffer_data  (const std::string& path_base);


    public:
        BufTokens buf_tokens_;

        TextDiff () = delete;
        TextDiff (const std::string& path_base);
       ~TextDiff ();

        const char* get_buffer_data () const;
        std::size_t get_num_symbols () const;
       
        void create_buffer_tokens ();
}; // class TextDiff

}; // namespace Differenciator


//-----------------------------------------------------------------------------

#endif // PARSING_TREE_H_INCLUDED

