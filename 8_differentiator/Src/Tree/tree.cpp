
#include "tree.hpp"
#include "parsing_text.h"

//-----------------------------------------------------------------------------

namespace Differenciator
{

static const int MAX_BUFF = 4096; 

//---------

Tree::Tree (const std::string& name) :
    name_ {name},
    root_ {nullptr},
    size_ {0}
{}

//---------

Tree::~Tree ()
{}

//----------

void Tree::dump (Mode mode, const char* path_name_without_end)
{
    assert (path_name_without_end);

    char path_name [MAX_BUFF] = {};

    if (mode == Mode::DEBUG)
        sprintf (path_name, "%s_db.dot",  path_name_without_end);
    else
        sprintf (path_name, "%s_rls.dot", path_name_without_end);

    FILE*   dump = fopen (path_name, "wb");
    assert (dump);

    fprintf (dump,  "digraph Tree {\n\n"

                    "    node [shape"  " = \"circle\", " "style" " = \"filled\", fillcolor = \"red\"," 
                              "fontcolor = \"#000000\", ""margin"" = \"0.01\"];\n"

                    "    rankdir = \"TB\";\n"

                    "    label   = \"Tree Graph\";\n\n");

    if (mode == Mode::DEBUG)
        print_graph_tree (Mode::DEBUG,   root_, dump);
    else 
        print_graph_tree (Mode::RELEASE, root_, dump);

    fprintf (dump,  "}\n");

    fclose  (dump);

    if (mode == Mode::DEBUG)
        vssystem ("dot -Tjpeg %s -o %s_db.jpeg",  path_name, path_name_without_end);
    else 
        vssystem ("dot -Tjpeg %s -o %s_rls.jpeg", path_name, path_name_without_end);

}


//---------

int vssystem (const char* command, ...) 
{
    assert (command);

    char    buff [MAX_BUFF] = {};
    va_list args;

    va_start (args, command);
    vsprintf (buff, command, args); 
    va_end   (args);

    return system (buff);
}

//----------

const NodeTree* const Tree::print_graph_tree (const Mode mode, const NodeTree* const prnt_node, FILE* dump)
{
    assert(this);

    if (mode == Mode::DEBUG) 
    {
        fprintf (dump,  "    \"_%p\" ["
                                        "label = \"{ "
                                                "{parent\\n (%p)} |", 
                                prnt_node,                   prnt_node->parent_);

        prnt_node->print_data  (prnt_node, dump);

        fprintf (dump,                         "| {me\\n (%p)} |"
                                                 " {left\\n (%p) |"
                                                  " right\\n (%p)} }\",",
                                                          prnt_node, 
                                                             prnt_node->left_,
                                                              prnt_node->right_);

        prnt_node->choose_param (prnt_node, dump);

        if (prnt_node->parent_)
            fprintf (dump, "    \"_%p\"->\"_%p\";\n",  prnt_node, prnt_node->parent_);
       
        if (prnt_node->left_)
            fprintf (dump, "    \"_%p\"->\"_%p\";\n",  prnt_node, prnt_node->left_);

        if (prnt_node->right_)
            fprintf (dump, "    \"_%p\"->\"_%p\";\n",  prnt_node, prnt_node->right_);
    }
    else 
    {
        fprintf (dump,  "    \"_%p\" [  "
                                        "label = \"{",
                                prnt_node);

        prnt_node->print_data  (prnt_node, dump);

        fprintf (dump,                   "}\"");

        prnt_node->choose_param (prnt_node, dump);
      
        if (prnt_node->left_)
            fprintf (dump, "    \"_%p\"->\"_%p\";\n",  prnt_node, prnt_node->left_);

        if (prnt_node->right_)
            fprintf (dump, "    \"_%p\"->\"_%p\";\n",  prnt_node, prnt_node->right_);        
    }

    fprintf(dump, "\n\n");

    if (prnt_node->right_ != nullptr)
        print_graph_tree(mode, prnt_node->left_,  dump);

    if (prnt_node->left_  != nullptr)
        print_graph_tree(mode, prnt_node->right_, dump);

    return prnt_node;
}

//-----------

void NodeTree::print_data (const NodeTree* const prnt_node, FILE* dump) const
{
    assert (prnt_node);
    assert (dump);

    switch (type_)
    {
        case TokenType::NUMB: fprintf (dump, " {type \\n (NUMB) | "
                                              "value\\n (%ld)}" , value_numb_);
                              break;

        case TokenType::VARB: fprintf (dump, " {type \\n (VARB) | "
                                              "value\\n (%c)}"  , value_varb_);
                              break;

        case TokenType::OPER: fprintf (dump, " {type \\n (OPER) | "
                                              "value\\n (%c)}"  , value_oper_);
                              break;

        default:              printf  ("ERROR! Type:\n");
                              break;
    }

}

//------------

void NodeTree::choose_param (const NodeTree* const prnt_node, FILE* dump) const
{
    assert (prnt_node);
    assert (dump);

    switch (type_)
    {
        case TokenType::NUMB: fprintf (dump, "fillcolor = \"palegreen\", "
                                            "shape"  " = \"record\"];\n");
                              break;

        case TokenType::VARB: fprintf (dump, "fillcolor = \"lightpink\", "
                                            "shape"  " = \"record\"];\n");
                              break;

        case TokenType::OPER: fprintf (dump, "fillcolor = \"lightcyan2\", "
                                            "shape"  " = \"record\"];\n");
                              break;

        default:              printf  ("ERROR! Type:\n");
                              break;
    }    

}

}; // using namespace Differenciator

//-----------------------------------------------------------------------------
