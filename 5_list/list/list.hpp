
#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

//-----------------------------------------------------------------------------

static const char* UNKNOWN_NAME = "UNKNOWN NAME";

static const int EMPTY = 0;

//-----------------------------------------------------------------------------

struct node {
	double data_ = 0;
	node*  prev_ = nullptr;
	node*  next_ = nullptr;
};

//-----------------------------------------------------------------------------

class List {

	public:

		// constructors
		List();
		List(                   const char* name = UNKNOWN_NAME);
		List(const double data, const char* name = UNKNOWN_NAME);

		List(const List&) = delete;

		// distructors
	   ~List();

	   	// operators
	   	const List& operator = (const List&) = delete;

	   	// capacities
	   	bool empty() const noexcept;
	   	int  size()  const noexcept;

	   	// position
	   	const node* begin() const noexcept;
	   	const node* end()   const noexcept;

	   	//! methods

		void push_back(const double data);
		void  pop_back();

		void push_front(const double data);
		void  pop_front();

		void dump()  const noexcept;
		void print() const noexcept; 	   	

		void clear();
		void swap();

	private: 
		int   cur_size_ = 0;
		node* head_     = nullptr;
		node* tail_     = nullptr;
		char* name_     = nullptr;
};


//-----------------------------------------------------------------------------

#endif // LIST_HPP_INCLUDED