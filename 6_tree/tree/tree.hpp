
#ifndef TREE_HPP_INCLUDED
#define TREE_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream> 
#include <fstream>
#include <ctime>
#include <string>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>

#include "settings.h"

//-----------------------------------------------------------------------------

class NodeTree
{
    public:

        std::string data_   = nullptr; 
        NodeTree*   left_   = nullptr;
        NodeTree*   right_  = nullptr;
        NodeTree*   parent_ = nullptr;
};
    
//!

class Tree
{
    private:

        //--------------------------------------------------

        std::string name_ = nullptr;
        NodeTree*   root_ = nullptr;

        //--------------------------------------------------

        NodeTree* insert(NodeTree* insrt_node, char* const data)
        {

        }

        //--------------------------------------------------

        void graph() const noexcept
        {
            FILE* graph = fopen("./txt/graph_tree.dot", "wb");
            assert(graph);

            fprintf(graph, "digraph Tree {\n\n");

            fprintf(graph, "\tnode [shape = \"circle\", style = \"filled\", fillcolor = \"red\",");
            fprintf(graph, "  fontcolor = \"#000000\", margin = \"0.01\"];\n");
            fprintf(graph, "\trankdir = \"TB\";\n\n");
            fprintf(graph, "\tlabel = \"Tree Graph\";\n");

            fprintf(graph, "\n");

            print_graph_tree(root_, graph);

            fprintf(graph, "}\n");

            fclose(graph);

            system("dot -Tjpeg ./txt/graph_tree.dot -o./txt/graph_tree.jpeg");
        }

        //--------------------------------------------------

        void print_dump_tree(NodeTree* prnt_node, FILE* output) const noexcept
        {
            if (prnt_node == nullptr)
                return;

            fprintf(output, "[%p] data  = {%p} left   = {%p}"  ,prnt_node        , prnt_node->data_   , prnt_node->left_);
            fprintf(output,     " right = {%p} parent = {%p}\n",prnt_node->right_, prnt_node->parent_);

            if (prnt_node->right_ != nullptr)
                print_dump_tree(prnt_node->right_, output);

            if (prnt_node->left_  != nullptr)
                print_dump_tree(prnt_node->left_,  output);
        }

        //--------------------------------------------------

        void print_graph_tree(NodeTree* prnt_node, FILE* output) const noexcept
        {

        }

        //--------------------------------------------------

    public:

        //--------------------------------------------------

        Tree() :
            name_(new std::string [UNKNOWN_NAME.length() + 1])
        {
            strcpy(name_, UNKNOWN_NAME);
        }

        //--------------------------------------------------

        Tree(std::string name) :
            name_(new std::string [name.length() + 1])
        {
            strcpy(name_, name);
        }

        //--------------------------------------------------

       ~Tree()
        {
            delete [] name_;
            delete    root_;

            name_ = nullptr;
            root_ = nullptr;
        }    

        //--------------------------------------------------

        void insert(char* const data)
        {
            root_ = insert(root_, data);
        }

        //--------------------------------------------------
    
        void dump() const noexcept
        {
            FILE* dump = fopen("./txt/dump_tree.txt", "wb");
            assert(dump);

            fprintf(dump, "\n******************************************************\n");

            time_t now = time(0);

            fprintf(dump, "\t%s   \n", ctime(&now));
            fprintf(dump, "\t\tTree:\n\n");

            fprintf(dump, "Tree (OK) [%p] \"%s\"\n", this, name_);

            print_dump_tree(root_, dump);

            fprintf(dump, "\n******************************************************\n");

            fclose(dump);

            graph();
        }

        //--------------------------------------------------

};

//-----------------------------------------------------------------------------

#endif // TREE_HPP_INCLUDED