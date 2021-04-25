
#include "tree.hpp"

//-----------------------------------------------------------------------------

Tree::Tree() :
    name_(UNKNOWN_NAME)
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::Tree(std::string name) :
    name_(name)
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::~Tree()
{
    assert(this);

    // destruct root_
    root_ = nullptr;
}

//-----------------------------------------------------------------------------

void Tree::dump(Mode mode, std::string file_path)
{
    assert(this);

    std::ofstream dump(file_path);
    assert(dump);

    dump << std::endl << "******************************************************" << std::endl;

    dump << "\t\t"        << return_current_time_and_date() << std::endl;
    dump << "\t\t\tTree:" << std::endl                      << std::endl;


    dump << "Tree (OK) [" << this << "] \"" << name_ << "\" {" << std::endl;

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

void Tree::print_dump_tree(NodeTree* prnt_node, std::ofstream& output)
{
    assert(this);

    if (prnt_node == nullptr)
        return;

    output <<   "data = {" << prnt_node->data_   << "}"
           <<   "left = {" << prnt_node->left_   << "}"
           <<  "right = {" << prnt_node->right_  << "}"
           << "parent = {" << prnt_node->parent_ << "}" << std::endl;

    if (prnt_node->right_ != nullptr)
        print_dump_tree(prnt_node->right_, output);

    if (prnt_node->left_  != nullptr)
        print_dump_tree(prnt_node->left_,  output);
}

//-----------------------------------------------------------------------------

void Tree::graph(Mode mode)
{
    assert(this);

    std::string file_path = "./txt/graph_tree_db.dot";

    if (mode == Mode::RELEASE)
        file_path = "./txt/graph_tree_rls.dot";


    std::ofstream graph(file_path);
    assert(graph);       


    graph << "digraph Tree {" << std::endl << std::endl;

    graph << "\tnode [shape = \"circle\", style = \"filled\", fillcolor = \"red\","
          <<     "fontcolor = \"#000000\", margin = \"0.01\"];\n"
          << "\trankdir = \"TB\";\n\n"
          << "\tlabel = \"Tree Graph\";\n";

    graph << std::endl;

    if (mode == Mode::DEBUG) {
        print_graph_tree(Mode::DEBUG,   root_, graph);
    }
    else 
        print_graph_tree(Mode::RELEASE, root_, graph);

    graph << "}" << std::endl;

    graph.close();

    if (mode == Mode::DEBUG)
        system("dot -Tjpeg ./txt/graph_tree_db.dot  -o./txt/graph_tree_db.jpeg");
    else 
        system("dot -Tjpeg ./txt/graph_tree_rls.dot -o./txt/graph_tree_rls.jpeg");
}

//-----------------------------------------------------------------------------

void Tree::print_graph_tree(Mode mode, NodeTree* prnt_node, std::ofstream& output)
{
    assert(this);

    if (prnt_node == nullptr)
        return;

    output << "\t\"V" << prnt_node << "\"[shape = \"record\", fillcolor=\"lightcyan2\", " <<
              "label = \""   << 
              "  parent\\n"  << prnt_node->parent_ <<
              "    data\\n"  << prnt_node->data_   <<
              " |    me\\n"  << prnt_node          << 
              " | {prev\\n(" << prnt_node->left_   << ")"    <<
              " |  next\\n(" << prnt_node->right_  << ")}"   <<  std::endl;


    if (prnt_node->right_ != nullptr)
        print_graph_tree(mode, prnt_node->right_, output);

    if (prnt_node->left_  != nullptr)
        print_graph_tree(mode, prnt_node->left_,  output);
}

//-----------------------------------------------------------------------------