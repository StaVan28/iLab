
#ifndef AKINATOR_TREE_HPP_INCLUDED
#define AKINATOR_TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "akinator_settings.hpp"
#include "tree.hpp"

//-----------------------------------------------------------------------------

class AkinatorTree : public Tree
{
    private:

        std::string base_ = nullptr;

        void fill_tree(const std::string base);

    public:

        AkinatorTree();
        AkinatorTree(const std::string base);

       ~AkinatorTree();
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_TREE_HPP_INCLUDED