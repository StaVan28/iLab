
#include "tree.hpp"

//-----------------------------------------------------------------------------

Tree::Tree() :
    name_ {UNKNOWN_NAME}
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::Tree(const std::string name) :
    name_ {name}
{
    assert(this);
}

//-----------------------------------------------------------------------------

Tree::~Tree()
{
    assert(this);

    clear();

    root_ = nullptr;
    size_ = 0;
}

//-----------------------------------------------------------------------------

bool Tree::insert(const std::string& data)
{
    bool result = insert(root_, data);

    if (result)
        size_++;

    return result;
}

//!

bool Tree::insert(NodeTree* const insrt_node, const std::string& data)
{
    if (root_ == insrt_node && empty()) 
    {
        root_ = new NodeTree(data, nullptr);
        return true;
    }

    if (data < insrt_node->data_) 
    {
        if (!insrt_node->left_) 
        {
            insrt_node->left_ = new NodeTree(data, insrt_node);
            return true;
        } 
        else 
            return insert(insrt_node->left_, data);
    } 
    else if (data > insrt_node->data_) 
    {
        if (!insrt_node->right_) 
        {
            insrt_node->right_ = new NodeTree(data, insrt_node);
            return true;
        } 
        else 
            return insert(insrt_node->right_, data);
    } 
    else 
        return false;
}


//-----------------------------------------------------------------------------

bool Tree::remove(const std::string& rmv_value) 
{   
    if (empty()) 
        return false;

    bool result = remove(root_, rmv_value);
    
    if (result) 
        size_--;

    return result;
}

//!

bool Tree::remove(NodeTree* srch_node, const std::string& rmv_data)
{
    if (!srch_node) 
        return false;
    
    if (srch_node->data_ == rmv_data) 
    {
        if (srch_node->left_ && srch_node->right_)
        {
            // don't use
            return true;
        } 
        else if (srch_node->left_ || srch_node->right_) 
        {
            NodeTree* non_null = nullptr;

            if (srch_node->left_)
                non_null = srch_node->left_;
            else
                non_null = srch_node->right_;  


            if (srch_node == root_) 
                root_ = non_null;
            else if (rmv_data < srch_node->parent_->data_) 
            {
                srch_node->parent_->left_ = non_null;
                
                if (srch_node->left_) 
                    srch_node->left_->parent_  = srch_node->parent_;
                else
                    srch_node->right_->parent_ = srch_node->parent_;                    
            }
            else 
            {
                srch_node->parent_->right_ = non_null;

                if (srch_node->left_) 
                    srch_node->left_->parent_  = srch_node->parent_;
                else
                    srch_node->right_->parent_ = srch_node->parent_;   
            }

            delete srch_node;
            return true;
        } 
        else 
        {
            if (srch_node == root_)
                root_ = nullptr;
            else if (rmv_data < srch_node->parent_->data_)
                srch_node->parent_->left_  = nullptr;
            else
                srch_node->parent_->right_ = nullptr;

            delete srch_node;
            return true;
        }
    } 
    else if (rmv_data < srch_node->data_)
        return remove(srch_node->left_ , rmv_data);
    else
        return remove(srch_node->right_, rmv_data);
}

//-----------------------------------------------------------------------------

bool Tree::clear()
{
    return clear(root_);
}

//!

bool Tree::clear(NodeTree* clr_node)
{
    if (empty())
        return false;

    if (clr_node->left_ != nullptr)
        clear(clr_node->left_);

    if (clr_node->right_ != nullptr)
        clear(clr_node->right_);

    delete clr_node;
    return true;
}

//-----------------------------------------------------------------------------


bool Tree::find_max(std::string ret_data) const
{
    return find_max(root_, ret_data);
}

//!

bool Tree::find_max(const NodeTree* const max_node, std::string ret_data) const
{
    if (max_node == nullptr) 
    {
        return false;
    }
    else if (!max_node->right_) 
    {
        ret_data = max_node->data_;
        return true;
    }

    return find_max(max_node->right_, ret_data);
}

//-----------------------------------------------------------------------------

bool Tree::find_min(std::string ret_data) const
{
    return find_min(root_, ret_data);
}

//!

bool Tree::find_min(const NodeTree* const min_node, std::string ret_data) const
{
    if (min_node == nullptr) 
    {
        return false;
    } 
    else if (!min_node->left_) 
    {
        ret_data = min_node->data_;
        return true;
    }

    return find_min(min_node->left_, ret_data);
}

//-----------------------------------------------------------------------------

void Tree::dump(const Mode mode, const std::string file_path)
{
    assert(this);

    std::ofstream dump(file_path);
    assert(dump);

    dump << std::endl << "******************************************************" << std::endl;


    dump << "\t\t"        << current_time_and_date() << std::endl;
    dump << "\t\t\tTree:" << std::endl               << std::endl;


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
    else {
        print_graph_tree(Mode::RELEASE, root_, graph);
    }

    graph << "}" << std::endl;

    graph.close();


    if (mode == Mode::DEBUG)
        system("dot -Tjpeg ./txt/graph_tree_db.dot  -o./txt/graph_tree_db.jpeg");
    else 
        system("dot -Tjpeg ./txt/graph_tree_rls.dot -o./txt/graph_tree_rls.jpeg");
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

bool Tree::empty() const noexcept 
{
    return size_ == EMPTY;
}

//!
std::size_t Tree::size() const noexcept
{
    return size_;
}

//-----------------------------------------------------------------------------