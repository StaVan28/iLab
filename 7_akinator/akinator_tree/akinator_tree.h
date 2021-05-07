
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

        void add_root      (std::size_t counter, std::size_t bracket_counter);
        void add_left_node (std::size_t counter, std::size_t bracket_counter, const TreeNode* const prnt_node);
        void add_right_node(std::size_t counter, std::size_t bracket_counter, const TreeNode* const prnt_node);

    public:

        AkinatorTree();
        AkinatorTree(const std::string base);

       ~AkinatorTree();
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_TREE_HPP_INCLUDED