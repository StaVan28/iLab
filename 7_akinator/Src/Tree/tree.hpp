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

        void create_tree_from_buf(const char* buffer_data);
        void create_root_node(NodeTree* tmp_new_node, NodeTree* tmp_prmt_node, const char* buffer_data, std::size_t indx_buf);
        void skip_delimiters(const char* buf_data, std::size_t indx_buf);
            
        bool tree_empty() const;
        bool clear(NodeTree* clr_node);

    public:

        AkinatorTree() = delete;
        AkinatorTree(const std::string path_base);
       ~AkinatorTree();

};

//--------------------------------------------------

#endif //TREE