
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "settings.h"
#include "node_diff.h"

//-----------------------------------------------------------------------------

enum class Mode : int 
{
    DEBUG,
    RELEASE,
};

//-----------------------------------------------------------------------------

namespace Differenciator
{

class Tree
{
    private:

        const NodeDiff* const print_graph_tree (const Mode mode, const NodeDiff* const prnt_node, FILE* dump);

    public:

        std::string name_;
        NodeDiff*   root_ = nullptr;
        std::size_t size_ = 0;

        Tree();
        Tree(const std::string& name);

       ~Tree();
    
        void dump (Mode mode = Mode::DEBUG, const char* path_name_without_end = "./Txt/dump_tree");

}; // class Tree

int vssystem (const char* command, ...) __attribute__((format(printf, 1, 2)));

}; // using namespace Differenciator


//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED