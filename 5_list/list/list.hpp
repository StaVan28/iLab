//-----------------------------------------------------------------------------

template <typename Data_t>
List<Data_t>::List() :
    name_(new char[strlen(UNKNOWN_NAME) + 1])
{
    strcpy(name_, UNKNOWN_NAME);
}

//-----------------------------------------------------------------------------

template <typename Data_t>
List<Data_t>::List(const char* const name) :
    name_(new char[strlen(name) + 1])
{
    strcpy(name_, name);
}

//-----------------------------------------------------------------------------

template <typename Data_t>
List<Data_t>::~List()
{
    dump();

    clear();

    delete [] name_;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::push_tail(const Data_t data)
{
    insert(position::AFTER, end(), data);
}

//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::push_head(const Data_t data)
{
    insert(position::BEFORE, begin(), data);
}

//-----------------------------------------------------------------------------

template <typename Data_t>
Data_t List<Data_t>::pop_head()
{
    return erase(begin());
}

//-----------------------------------------------------------------------------

template <typename Data_t>
Data_t List<Data_t>::pop_tail()
{
    return erase(end());
}

//-----------------------------------------------------------------------------

template <typename Data_t>
Node<Data_t>* List<Data_t>::search_node(const int indx) const noexcept
{
    Node<Data_t>* srch_node = nullptr;
    int            tmp_indx = 0;

    if (indx > size_)
        return nullptr;

    if (indx < 0)
        return nullptr;

    if (indx < size_ / 2) {
        
        tmp_indx  = 0;
        srch_node = head_;

        while (srch_node && tmp_indx < indx) {
            srch_node = srch_node->next_;
            tmp_indx++;
        }
    }
    else {
        
        tmp_indx  = size_ - 1;
        srch_node = tail_;

        while (srch_node && tmp_indx > indx) {
            srch_node = srch_node->prev_;
            tmp_indx--;
        }
    }

    return srch_node;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::insert(position indx_pos, const int indx, const Data_t data)
{
    Node<Data_t>*  srch_node = search_node(indx);
    Node<Data_t>* insrt_node = nullptr;

    if (srch_node == nullptr && indx != NO_ELEMENT)
        return;

    if (indx < 0)
        return;

    insrt_node = new Node<Data_t>;
    assert(insrt_node);

    insrt_node->data_ = data;

    if (empty()) {
        head_ = insrt_node;
        tail_ = insrt_node;

        size_++;
        return;
    }

    if (indx_pos == position::BEFORE) {
        if (indx == begin()) {
            insrt_node->next_ = head_;
            insrt_node->prev_ = nullptr;

            head_->prev_ = insrt_node;
            head_        = insrt_node;
        }
        else {
            insrt_node->next_ = srch_node;
            insrt_node->prev_ = srch_node->prev_;

            srch_node->prev_->next_ = insrt_node;
            srch_node->prev_        = insrt_node;
        }
    }

    if (indx_pos == position::AFTER) {
        if (indx == end()) {
            insrt_node->next_ = nullptr;
            insrt_node->prev_ = tail_;

            tail_->next_ = insrt_node;
            tail_        = insrt_node;
        }
        else {
            insrt_node->next_ = srch_node->next_;
            insrt_node->prev_ = srch_node;

            srch_node->next_->prev_ = insrt_node;
            srch_node->next_        = insrt_node;
        }
    }

    size_++;
    return;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
Data_t List<Data_t>::erase(const int indx)
{
    Node<Data_t>* del_node = search_node(indx);
    double        del_data = DOUBLE_POISON;

    if (empty())
        return DOUBLE_POISON;
 
    if (size_ == ONE_ELEMENT) {

        del_data = del_node->data_;
        delete del_node;

        head_ = nullptr;
        tail_ = nullptr;

        size_--;

        return del_data;
    }

    if (indx == begin()) {
        head_        = head_->next_;
        head_->prev_ = nullptr;    
    }
    else if (indx == end()) {
        tail_        = tail_->prev_;
        tail_->next_ = nullptr;
    }
    else {
        del_node->next_->prev_ = del_node->prev_;
        del_node->prev_->next_ = del_node->next_;
    }

    del_data = del_node->data_;
    delete del_node;
 
    size_--;

    return del_data;
}    


//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::clear()
{
    Node<Data_t>*  clr_node = head_;
    Node<Data_t>* next_node = nullptr;

    if (head_ == nullptr)
        return;

    while (clr_node) {
        next_node = clr_node->next_;
        delete clr_node;
        clr_node  = next_node;        
    }

    head_ = nullptr;
    tail_ = nullptr;

    size_ = 0;
}

//-----------------------------------------------------------------------------

// it is not noexcept
template <typename Data_t>
void List<Data_t>::graph() const noexcept
{
    ofstream graph("./txt/graph_list.dot");
    assert(graph);

    graph << "digraph List {"   << endl << endl;

    graph << "\tnode [shape = \"circle\", style = \"filled\", fillcolor = \"salmon1\",";
    graph << " fontcolor = \"#000000\", margin = \"0.01\"];" << endl;
    graph << "\tedge [style = \"dashed\"];" << endl;
    graph << "\trankdir = \"LR\"" << endl << endl;

    graph << "\tlabel = \"List Graph\";\n" << endl;


    size_t counter = 0;
    for (Node<Data_t>* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_) {
        counter++;
        graph << "\t\"V" << tmp_node << "\"[shape = \"record\", fillcolor=\"lightcyan2\", ";
        graph << "label = \""   << 
                 "    data\\n"  << tmp_node->data_ <<
                 " |    me\\n"  << tmp_node        << 
                 " | {prev\\n(" << tmp_node->prev_ << ")"    << 
                 " |  next\\n(" << tmp_node->next_ << ")}"   << 
                 " | <f0> "     << counter         << "\"];" << endl;
    }

    graph << endl;

    for (Node<Data_t>* tmp_node = tail_; tmp_node != nullptr; tmp_node = tmp_node->prev_)
    {
        if (tmp_node->next_ != nullptr) {
            graph << "\t\"V"   << tmp_node;
            graph << "\"->\"V" << tmp_node->next_ << "\";" << endl;
        }
    }

    for (Node<Data_t>* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_)
    {
        if (tmp_node->prev_ != nullptr) {
            graph << "\t\"V"   << tmp_node;
            graph << "\"->\"V" << tmp_node->prev_ << "\";" << endl;
        }
    }


    graph << "}" << endl;

    graph.close();    

    system("dot -Tjpeg -o./txt/graph_list.jpeg ./txt/graph_list.dot");
}

//-----------------------------------------------------------------------------
// output to custom dump file
template <typename Data_t>
void List<Data_t>::dump()
{
    ofstream dump("./txt/dump_list.txt");
    assert(dump);

    print_form(dump);

    dump.close();

    graph();
    log();
}

//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::log()
{
    ofstream log("./txt/log_list.txt", ios::app);
    assert(log);

    print_form(log);

    log.close();        
}

//-----------------------------------------------------------------------------

template <typename Data_t>
void List<Data_t>::print_form(ofstream& my_stream)
{
    my_stream << endl << "******************************************************" << endl;
    
    time_t now = time(0);
   
    my_stream << "\t\t"        << ctime(&now) << endl;
    my_stream << "\t\t\tList:" << endl        << endl;

    my_stream << "List (OK) [" << this << "] \"" << name_ << "\" {" << endl << endl;

    my_stream << "\tsize = " << size_ << endl;
    my_stream << "\thead = " << head_ << endl;
    my_stream << "\ttail = " << tail_ << endl << endl;

    for (Node<Data_t>* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_) {
        my_stream << "\t[" << tmp_node << "]" << \
                " data = " << tmp_node->data_ << \
                " next = " << tmp_node->next_ << \
                " prev = " << tmp_node->prev_ << endl;
    }

    my_stream << endl << "******************************************************" << endl;    
}

//-----------------------------------------------------------------------------

template <typename Data_t>
bool List<Data_t>::empty() const noexcept
{
    return size_ == EMPTY;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
int List<Data_t>::size()  const noexcept
{
    return size_;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
int List<Data_t>::begin() const noexcept
{
    return 0;
}

//-----------------------------------------------------------------------------

template <typename Data_t>
int List<Data_t>::end() const noexcept
{
    return size_ - 1;
}

//-----------------------------------------------------------------------------
