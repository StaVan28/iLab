//--------------------------------------------------

#include "tree.hpp"

//--------------------------------------------------

AkinatorTree::AkinatorTree (const std::string& path_base) :
    path_base_ {path_base}
{
    assert (this);

    fill_akinator_tree();
}

//---------

AkinatorTree::~AkinatorTree()
{
    assert (this);
    
    clear (root_);

    root_ = 0;
    size_ = 0;
}

//---------

void AkinatorTree::fill_akinator_tree()
{
    Text parser_base (path_base_);

    Token*      buf_lexems = parser_base.create_buffer_lexems ();
    std::size_t num_lexem  = 0;
    
    root_ = fill_recurce_tree (buf_lexems, &num_lexem);

    printf("END recurse\n");

    dump (TreeDumpMode::DEBUG);

    delete [] buf_lexems;
}

//

NodeTree* AkinatorTree::fill_recurce_tree (Token* buf_lexems, std::size_t* num_lexem)
{
    if (buf_lexems[*num_lexem].type == TokenType::QUESTION)
    {
        NodeTree* cur_node = new NodeTree;
        cur_node->data_    = buf_lexems[*num_lexem].value_str;
        (*num_lexem)++;

        assert (buf_lexems[*num_lexem].value_oper == '<');
        (*num_lexem)++;

        cur_node->left_  = fill_recurce_tree (buf_lexems, num_lexem);
        cur_node->left_->parent_ = cur_node;

        assert (buf_lexems[*num_lexem].value_oper == '>');
        (*num_lexem)++;

        cur_node->right_ = fill_recurce_tree (buf_lexems, num_lexem);
        cur_node->right_->parent_ = cur_node;

        return cur_node;
    }
    else if (buf_lexems[*num_lexem].type == TokenType::ANSWER)
    {
        NodeTree* cur_node = new NodeTree;
        cur_node->data_    = buf_lexems[*num_lexem].value_str;
        (*num_lexem)++;

        return cur_node;
    }
    else if (buf_lexems[*num_lexem].type == TokenType::STOP)
    {
        printf ("STOP\n");
        return nullptr;
    }
    else 
    {
        printf("rec, UNKNOWN = {%s}[%d]\n", buf_lexems[*num_lexem].value_str.c_str(), *num_lexem);
        return nullptr;
    }
}

//---------

void AkinatorTree::fill_akinator_base()
{

}

//---------

bool AkinatorTree::tree_empty() const
{
    return size_ == EMPTY;
}

//---------

bool AkinatorTree::clear (NodeTree* clr_node)
{
    if (tree_empty())
        return false;

    if (clr_node->left_ != nullptr)
        clear (clr_node->left_);

    if (clr_node->right_ != nullptr)
        clear (clr_node->right_);

    delete clr_node;
    return true;
}

//---------


void AkinatorTree::dump(const TreeDumpMode mode, const std::string& file_path)
{
    assert(this);

    std::ofstream dump (file_path);

    dump << std::endl << "******************************************************" << std::endl;


    dump << "\t\t"        << current_time_and_date() << std::endl;
    dump << "\t\t\tTree:" << std::endl               << std::endl;


    dump << "Tree (OK) [" << this << "] {" << std::endl;

    dump << std::endl << "\tsize = " << size_ << std::endl << std::endl;

    print_dump_tree (root_, dump);

    dump << "}" << std::endl;


    dump << std::endl << "******************************************************" << std::endl;

    dump.close();

    if (mode == TreeDumpMode::DEBUG)
        graph (TreeDumpMode::DEBUG);
    else
        graph (TreeDumpMode::RELEASE);
}

//-----------------------------------------------------------------------------

void AkinatorTree::print_dump_tree (const NodeTree* const prnt_node, std::ofstream& output_file)
{
    assert (this);

    if (prnt_node == nullptr)
        return;

    output_file <<   "data = {" << prnt_node->data_   << "}"
                <<   "left = {" << prnt_node->left_   << "}"
                <<  "right = {" << prnt_node->right_  << "}"
                << "parent = {" << prnt_node->parent_ << "}" << std::endl;

    if (prnt_node->right_ != nullptr)
        print_dump_tree (prnt_node->right_, output_file);

    if (prnt_node->left_  != nullptr)
        print_dump_tree (prnt_node->left_,  output_file);
}

//-----------------------------------------------------------------------------

void AkinatorTree::graph (const TreeDumpMode mode)
{
    assert (this);

    std::string file_path = "./Txt/graph_tree_db.dot";

    if (mode == TreeDumpMode::RELEASE)
        file_path = "./Txt/graph_tree_rls.dot";


    std::ofstream graph (file_path);     


    graph << "digraph Tree {" << std::endl << std::endl;

    graph << "\tnode [shape = \"circle\", style = \"filled\", fillcolor = \"red\","
          <<     "fontcolor = \"#000000\", margin = \"0.01\"];\n"
          << "\trankdir = \"TB\";\n\n"
          << "\tlabel = \"Tree Graph\";\n";

    graph << std::endl;

    if (mode == TreeDumpMode::DEBUG) {
        print_graph_tree (TreeDumpMode::DEBUG,   root_, graph);
    }
    else {
        print_graph_tree (TreeDumpMode::RELEASE, root_, graph);
    }

    graph << "}" << std::endl;

    graph.close();


    if (mode == TreeDumpMode::DEBUG)
        system ("dot -Tjpeg ./Txt/graph_tree_db.dot  -o./Txt/graph_tree_db.jpeg");
    else 
        system ("dot -Tjpeg ./Txt/graph_tree_rls.dot -o./Txt/graph_tree_rls.jpeg");
}

//-----------------------------------------------------------------------------

void AkinatorTree::print_graph_tree (const TreeDumpMode mode, const NodeTree* const prnt_node, std::ofstream& output_file)
{
    assert (this);

    if (prnt_node == nullptr)
        return;


    if (mode == TreeDumpMode::DEBUG) 
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
        print_graph_tree (mode, prnt_node->right_, output_file);

    if (prnt_node->left_  != nullptr)
        print_graph_tree (mode, prnt_node->left_,  output_file);
}

//--------------------------------------------------
