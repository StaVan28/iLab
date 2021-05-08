
#ifndef AKINATOR_TREE_HPP_INCLUDED
#define AKINATOR_TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "akinator_settings.h"
#include "tree.hpp"
#include "text.h"

//-----------------------------------------------------------------------------

class AkinatorTree : public Tree
{
    private:

        std::string base_ = nullptr;

        void fill_tree(const std::string base);

        void      add_root(char* buffer);
        NodeTree* add_node(const PositionNode pos, char* buffer, std::size_t counter, 
                           NodeTree* const parent_node);

    public:

        AkinatorTree();
        AkinatorTree(const std::string base);

       ~AkinatorTree();
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_TREE_HPP_INCLUDED