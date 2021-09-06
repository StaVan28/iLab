#ifndef TREE
#define TREE

//--------------------------------------------------

#include "settings.hpp"

//--------------------------------------------------

class NodeTree
{
    public:

        std::string data_   = nullptr;
        NodeTree*   parent_ = nullptr;
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
 
        NodeTree()
        {}

        //!

        NodeTree(std::string data, NodeTree* parent) :
            data_   {data},
            parent_ {parent}
        {}
       
        //!

       ~NodeTree()
       {}
};

//--------------------------------------------------

class AkinatorTree
{
    private:

        NodeTree*   root_      = nullptr; 
        std::string path_base_ = nullptr;
        std::size_t size_      = 0;

        void fill_akinator_tree();
        void fill_akinator_base();

        void create_tree(const char* buffer_data);
            
        bool tree_empty() const;
        bool clear(NodeTree* clr_node);
    
    public:
        
        AkinatorTree() = delete;
        AkinatorTree(const std::string path_base);
       ~AkinatorTree();
       
};

//--------------------------------------------------

#endif //TREE