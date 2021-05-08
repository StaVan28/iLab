
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

    if (num_symbols == EMPTY_FILE)
        return;

    add_root(buffer);
}

//-----------------------------------------------------------------------------

void AkinatorTree::add_root(char* buffer)
{
    assert(this);
    assert(buffer);

    std::size_t counter      = 0;
    NodeTree*   current_node = nullptr;   

    add_node(PositionNode::ROOT, buffer, counter, current_node);
}

//!

NodeTree* AkinatorTree::add_node(const PositionNode pos, char* buffer, std::size_t counter, 
                                 NodeTree* const parent_node)
{
    assert(this);

    while (isspace(buffer[counter]) || buffer[counter] == BEGIN_NODE_SIGN) 
        counter++;

    if (buffer[counter] == QUESTION_SIGN || buffer[counter] == ANSWER_SIGN)
        counter++;
    else 
        printf("\nERROR!!!\n: counter -- [%lu], buffer synbol -- [%c]", counter, buffer[counter]);

    NodeTree* current_node = new NodeTree(&(buffer[counter]), parent_node);
    assert(current_node);

    while (buffer[counter] != QUESTION_SIGN || buffer[counter] != ANSWER_SIGN)
        counter++;

    if (buffer[counter] == QUESTION_SIGN || buffer[counter] == ANSWER_SIGN)
        counter++;
    else 
        printf("\nERROR!!!\n: counter -- [%lu], buffer synbol -- [%c]", counter, buffer[counter]);

    while (isspace(buffer[counter]) || buffer[counter] == END_NODE_SIGN || buffer[counter] == BEGIN_NODE_SIGN)
    {
        counter++;

        if (buffer[counter] == END_NODE_SIGN)
            return current_node;
    else 
        printf("\nERROR!!!\n: counter -- [%lu], buffer synbol -- [%c]", counter, buffer[counter]);
    }

    if (buffer[counter] == QUESTION_SIGN || buffer[counter] == ANSWER_SIGN)
    {
        current_node->left_  = add_node(PositionNode::LEFT,  buffer, counter, current_node);
        current_node->right_ = add_node(PositionNode::RIGHT, buffer, counter, current_node);
    }
}
//-----------------------------------------------------------------------------
