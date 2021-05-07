
#include "akinator_tree.h"

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree() :
    Tree  {AKINATOR_TREE_NAME},
    base_ {DEFAULT_BASE}
{
    assert(this);

    fill_tree(DEFAULT_BASE);
}

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree(const std::string base) :
    Tree  {AKINATOR_TREE_NAME},
    base_ {base}
{
    assert(this);

    fill_tree(base);
}

//-----------------------------------------------------------------------------

AkinatorTree::~AkinatorTree()
{
    assert(this);
}

//-----------------------------------------------------------------------------

void AkinatorTree::fill_tree(const std::string base)
{
    assert(this);

    AkinatorText base_parsing(base);

    char*       buffer      = base_parsing.buffer_data();
    std::size_t num_symbols = base_parsing.num_symbols();

    std::size_t counter         = 0;
    std::size_t bracket_counter = 0;

    if (num_symbols == EMPTY_FILE)
        return;

    while (counter < num_symbols)
    {
        while (isspace(buffer[counter]) ||
               buffer[counter] == '\0'  ||
               buffer[counter] == '\n'  ||
               buffer[counter] == '@'   ||
               buffer[counter] == '$'   ||
               buffer[counter] == '\"'  ||
               buffer[counter] == '}'   ||
               buffer[counter] == '{'     ) 
        {
            counter++;
        }

        

    }
}

//-----------------------------------------------------------------------------

