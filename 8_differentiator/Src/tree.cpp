
#include "tree.hpp"

//-----------------------------------------------------------------------------

Tree::Tree (const std::string& name) :
    name_ {name}
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::~Tree ()
{
    assert(this);

    root_ = nullptr;
    size_ = 0;
}

//-----------------------------------------------------------------------------

void Tree::dump(const Mode mode, const std::string& file_path)
{
    assert(this);

    std::ofstream dump(file_path);
    assert(dump);

    dump << std::endl << "******************************************************" << std::endl;

    dump << "\t\t\tTree:" << std::endl << std::endl;

    dump << "Tree (OK) [" << this << "] \"" << name_ << "\" {" << std::endl;

    dump << std::endl << "\tsize = " << size_ << std::endl << std::endl;

    print_dump_tree(root_, dump);

    dump << "}" << std::endl;


    dump << std::endl << "******************************************************" << std::endl;

    dump.close();

    if (mode == Mode::DEBUG)
        graph(Mode::DEBUG);
    else
        graph(Mode::RELEASE);
}

//-----------------------------------------------------------------------------

void Tree::print_dump_tree(const NodeTree* const prnt_node, std::ofstream& output_file)
{
    assert(this);

    if (prnt_node == nullptr)
        return;

    output_file <<   "data = {" << prnt_node->data_   << "}"
                <<   "left = {" << prnt_node->left_   << "}"
                <<  "right = {" << prnt_node->right_  << "}"
                << "parent = {" << prnt_node->parent_ << "}" << std::endl;

    if (prnt_node->right_ != nullptr)
        print_dump_tree(prnt_node->right_, output_file);

    if (prnt_node->left_  != nullptr)
        print_dump_tree(prnt_node->left_,  output_file);
}

//-----------------------------------------------------------------------------

void Tree::graph(const Mode mode)
{
    assert(this);

    std::string file_path = "./graph_tree_db.dot";

    if (mode == Mode::RELEASE)
        file_path = "./graph_tree_rls.dot";


    std::ofstream graph(file_path);
    assert(graph);       


    graph << "digraph Tree {" << std::endl << std::endl;

    graph << "\tnode [shape = \"circle\", style = \"filled\", fillcolor = \"red\","
          << "fontcolor = \"#000000\", margin = \"0.01\"];\n"
          << "\trankdir = \"TB\";\n\n"
          << "\tlabel = \"Tree Graph\";\n";

    graph << std::endl;

    if (mode == Mode::DEBUG) {
        print_graph_tree(Mode::DEBUG,   root_, graph);
    }
    else {
        print_graph_tree(Mode::RELEASE, root_, graph);
    }

    graph << "}" << std::endl;

    graph.close();


    if (mode == Mode::DEBUG)
        system("dot -Tjpeg ./graph_tree_db.dot  -o./graph_tree_db.jpeg");
    else 
        system("dot -Tjpeg ./graph_tree_rls.dot -o./graph_tree_rls.jpeg");

    getchar();
}

//-----------------------------------------------------------------------------

void Tree::print_graph_tree(const Mode mode, const NodeTree* const prnt_node, std::ofstream& output_file)
{
    assert(this);

    if (prnt_node == nullptr)
        return;


    if (mode == Mode::DEBUG) 
    {
        output_file << "\t\"" << prnt_node << "\" [shape = \"record\", fillcolor=\"lightcyan2\", " <<
                  "label = \""      << 
                  "{ {parent\\n ("  << prnt_node->parent_ << ") } |"     <<
                      "{data\\n ("  << prnt_node->data_   << ") } |"     <<
                        "{me\\n ("  << prnt_node          << ") } |"     <<
                      "{left\\n ("  << prnt_node->left_   << ")   |"     <<
                      "right\\n ("  << prnt_node->right_  << ") } }\"];" <<  std::endl;
     
        if (prnt_node->parent_)
            output_file << "\t\"" << prnt_node << "\"->\"" << prnt_node->parent_ << "\";" << std::endl;
       
        if (prnt_node->left_)
            output_file << "\t\"" << prnt_node << "\"->\"" << prnt_node->left_ << "\";" << std::endl;
       
        if (prnt_node->right_)
            output_file << "\t\"" << prnt_node << "\"->\"" << prnt_node->right_ << "\";" << std::endl;
    }
    else 
    {
        output_file << "\t\"" << prnt_node << "\" [shape = \"record\", fillcolor=\"lightcyan2\", " <<
                  "label = \""  << 
                  "{"  << prnt_node->data_   << "}\" ];" << std::endl;
      
        if (prnt_node->left_)
            output_file << "\t\"" << prnt_node << "\"->\"" << prnt_node->left_ << "\";" << std::endl;
       
        if (prnt_node->right_)
            output_file << "\t\"" << prnt_node << "\"->\"" << prnt_node->right_ << "\";" << std::endl;        
    }


    output_file << std::endl << std::endl;

    if (prnt_node->right_ != nullptr)
        print_graph_tree(mode, prnt_node->right_, output_file);

    if (prnt_node->left_  != nullptr)
        print_graph_tree(mode, prnt_node->left_,  output_file);
}

//-----------------------------------------------------------------------------
