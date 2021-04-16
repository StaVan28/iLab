
#include "list.hpp"

//-----------------------------------------------------------------------------

List::List() :
	name_(new char[strlen(UNKNOWN_NAME) + 1])
{
	strcpy(name_, UNKNOWN_NAME);
}

//-----------------------------------------------------------------------------

List::List(const char* name) :
	name_(new char[strlen(name) + 1])
{
	strcpy(name_, name);
}

//-----------------------------------------------------------------------------

List::~List()
{
	dump();

	clear();

	delete [] name_;
}

//-----------------------------------------------------------------------------

void List::push_tail(const double data)
{
	node* tmp_node = new node;
	assert(tmp_node);

	tmp_node->data_ = data;

	if (empty()) {

		head_ = tmp_node;
		tail_ = tmp_node;

		size_++;
		return;
	}

	tmp_node->next_ = nullptr;
	tmp_node->prev_ = tail_;

	tail_->next_ = tmp_node;
	tail_        = tmp_node;
	
	size_++;
}

//-----------------------------------------------------------------------------

void List::push_head(const double data)
{
	node* tmp_node = new node;
	assert(tmp_node);

	tmp_node->data_ = data;

	if (empty()) {

		head_ = tmp_node;
		tail_ = tmp_node;

		size_++;
		return;
	}

	tmp_node->next_ = head_;
	tmp_node->prev_ = nullptr;

	head_->prev_ = tmp_node;
	head_        = tmp_node;
	
	size_++;	
}

//-----------------------------------------------------------------------------

double List::pop_head()
{
    node*  tmp_node = head_;
    double tmp_data = NAN;

    if (empty())
        return NAN;
 
    if (size_ == ONE_ELEMENT) {

    	tmp_data = tmp_node->data_;
    	delete tmp_node;

    	head_ = nullptr;
    	tail_ = nullptr;

    	size_--;

    	return tmp_data;
    }

    head_        = head_->next_;
    head_->prev_ = nullptr;

    tmp_data = tmp_node->data_;
    delete tmp_node;
 
    size_--;

    return tmp_data;
}

//-----------------------------------------------------------------------------

double List::pop_tail()
{
    node*  tmp_node = tail_;
    double tmp_data = NAN;

    if (empty())
        return NAN;
 
    if (size_ == ONE_ELEMENT) {

    	tmp_data = tmp_node->data_;
    	delete tmp_node;

    	head_ = nullptr;
    	tail_ = nullptr;

    	size_--;

    	return tmp_data;
    }

    tail_        = tail_->prev_;
    tail_->next_ = nullptr;

    tmp_data = tmp_node->data_;
    delete tmp_node;
 
    size_--;

    return tmp_data;
}

//-----------------------------------------------------------------------------

node* List::search_node(int indx) const noexcept
{
	node* srch_node = nullptr;
	int   tmp_indx  = 0;

	if (indx > size_)
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

void List::clear()
{
	node*  tmp_node = head_;
	node* next_node = nullptr;

	if (head_ == nullptr)
		return;

	while (tmp_node) {
		next_node = tmp_node->next_;
		delete tmp_node;
		tmp_node  = next_node;		
	}

	head_ = nullptr;
	tail_ = nullptr;

	size_ = 0;
}

//-----------------------------------------------------------------------------

void List::dump()
{
	ofstream dump("./txt/dump_list.txt");
	assert(dump);

	print_form(dump);

	dump.close();

	graph();
	log();
}

//-----------------------------------------------------------------------------

void List::graph() const noexcept
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
    for (node* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_) {
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

    for (node* tmp_node = tail_; tmp_node != nullptr; tmp_node = tmp_node->prev_)
    {
        if (tmp_node->next_ != nullptr)
        	graph << "\t\"V" << tmp_node << "\"->\"V" << tmp_node->next_ << "\";" << endl;
    }

    for (node* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_)
    {
        if (tmp_node->prev_ != nullptr)
        	graph << "\t\"V" << tmp_node << "\"->\"V" << tmp_node->prev_ << "\";" << endl;
    }


	graph << "}" << endl;

	graph.close();	

	system("dot -Tjpeg -o./txt/graph_list.jpeg ./txt/graph_list.dot");
}

//-----------------------------------------------------------------------------

void List::log()
{
	ofstream log("./txt/log_list.txt", ios::app);
	assert(log);

	print_form(log);

	log.close();		
}

//-----------------------------------------------------------------------------

void List::print_form(ofstream& my_stream)
{
	my_stream << endl << "******************************************************" << endl;
	
	time_t now = time(0);
   
   	my_stream << "\t\t"        << ctime(&now) << endl;
	my_stream << "\t\t\tList:" << endl     << endl;

	my_stream << "List (OK) [" << this << "] \"" << name_ << "\" {" << endl << endl;

	my_stream << "\tsize = " << size_ << endl;
	my_stream << "\thead = " << head_ << endl;
	my_stream << "\ttail = " << tail_ << endl << endl;

	for (node* tmp_node = head_; tmp_node != nullptr; tmp_node = tmp_node->next_) {
		my_stream << "\t[" << tmp_node << "]" << \
				" data = " << tmp_node->data_ << \
				" next = " << tmp_node->next_ << \
				" prev = " << tmp_node->prev_ << endl;
	}

	my_stream << endl << "******************************************************" << endl;	
}

//-----------------------------------------------------------------------------

bool List::empty() const noexcept
{
	return size_ == EMPTY;
}

//-----------------------------------------------------------------------------

int  List::size()  const noexcept
{
	return size_;
}
