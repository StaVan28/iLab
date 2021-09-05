#ifndef TREE
#define TREE

//--------------------------------------------------

#include "settings.hpp"

//--------------------------------------------------

class NodeTree
{
    private:

        std::string data_   = nullptr;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;

    public:
        
        NodeTree() = delete;
        
        //!

        NodeTree(const std::string data, NodeTree* parent, 
                         NodeTree* left, NodeTree* right) :
            data_   {data},
            parent_ {parent},
            left_   {left},
            right_  {right}
        {}
       
        //!

       ~NodeTree()
       {}
};

//--------------------------------------------------

class AkinatorTree
{
    private:

        std::string path_base_ = nullptr;
        std::size_t size_      = 0;

        void fill_akinator_tree();
        void fill_akinator_base();
       
    public:
        
        AkinatorTree();
        AkinatorTree(const std::string path_base);
       ~AkinatorTree();
};

//--------------------------------------------------

#endif //TREE