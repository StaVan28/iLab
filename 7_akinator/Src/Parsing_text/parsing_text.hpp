#ifndef PARSING_TEXT
#define PARSING_TEXT

//--------------------------------------------------

#include "settings.hpp"

//---------------------------------------------------

enum class TokenType : int
{    
    STOP,
    ANSWER,
    QUESTION,
    OPER,
};

//---------------------------------------------------

struct Token
{
    TokenType type;

    std::string value_str; 
    char        value_oper;

    Token()
    {}

   ~Token()
    {}
};

//--------------------------------------------------

class Text
{
    private:

        std::size_t num_symbols_ = 0;
        char*       buf_data_    = nullptr;

        void num_symbols_in_file (FILE* akin_base);
        void create_buffer_data  (const std::string& path_base);

        std::size_t num_lexems_in_buf ();

        void skip_space (char* buf_data_, std::size_t* indx_buf);

    public:

        Text () = delete;
        Text (const std::string& path_base);
       ~Text ();

        const char* get_buffer_data () const;
        std::size_t get_num_symbols () const;
       
        Token* create_buffer_lexems ();
};

//--------------------------------------------------

#endif //PARSING_TEXT
