
#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <string.h>
using namespace std;

#include "settings.hpp"

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
		List(const char* name);

		List(const List&) = delete;

		// distructor
	   ~List();

		// operators
		const List& operator = (const List&) = delete;

		// capacities
		bool empty() const noexcept;
		int  size()  const noexcept;

		//! methods
		void   push_head(const double data);
		double pop_head();

		void   push_tail(const double data);
		double pop_tail();

		void dump();

		void clear();
		void swap();

	private: 
		int   size_ = 0;
		node* head_ = nullptr;
		node* tail_ = nullptr;
		char* name_ = nullptr;

		node* search_node(int indx) const noexcept;

		void graph() const noexcept;
		void log();
		void print_form(ofstream& my_stream);
};


//-----------------------------------------------------------------------------

#endif // LIST_HPP_INCLUDED