
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

List::List(const double data, const char* name) : 
	name_(new char[strlen(name) + 1])
{
	strcpy(name_, name);

	push_front(data);
}

//-----------------------------------------------------------------------------

List::~List()
{
	clear();

	delete [] name_;
}

//-----------------------------------------------------------------------------

void List::push_front(const double data)
{
	node* tmp_node = new node;
	assert(tmp_node);

	tmp_node->data_ = data;

	if (empty()) {

		head_ = tmp_node;
		tail_ = tmp_node;

		return;
	}

	tmp_node->next_ = head_;
	tmp_node->prev_ = nullptr;

	head_->prev_ = tmp_node;
	head_        = tmp_node;
	
	cur_size_++;
}

//-----------------------------------------------------------------------------

void List::clear()
{
	node*  tmp_node = head_;
	node* next_node = nullptr;

	while (tmp_node) {
		next_node = tmp_node->next_;
		delete tmp_node;
		tmp_node  = next_node;		
	}
}

//-----------------------------------------------------------------------------

bool List::empty() const noexcept
{
	return cur_size_ == EMPTY;
}

//-----------------------------------------------------------------------------

int  List::size()  const noexcept
{
	return cur_size_;
}

//-----------------------------------------------------------------------------

const node* List::begin() const noexcept
{
	return head_;
}

//-----------------------------------------------------------------------------

const node* List::end() const noexcept
{
	return tail_;
}

//-----------------------------------------------------------------------------