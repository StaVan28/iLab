
#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "list_iterators.hpp"

//-----------------------------------------------------------------------------

struct node {
	double field = 0;
	node*  prev  = nullptr;
	node*  next  = nullptr;
};

//-----------------------------------------------------------------------------

class List {

	public:

		// typedef own iterators 
		typedef List_iterator       <node>       iterator;
		typedef List_iterator <const node> const_iterator;

		// iterators 
		iterator begin();
		iterator end();

		const_iterator const_begin() const;
		const_iterator const_end()   const;

		// constructors
		List();
		List(const double value);
		List(const List&) = delete;

		// distructors
	   ~List();

	   	// operators
	   	List& operator = (const List&) = delete;

	   	// capacities
	   	bool   empty() const noexcept;
	   	size_t size()  const noexcept;

	   	//! methods

	   	//	inserts value before position
	   	double insert (const_iterator position,                  const double value);
	   	double insert (const_iterator position, size_t quantity, const double value);

	   	// Inserts a new element into the container directly before pos.
	   	double emplace(const_iterator position,                  const double value);
	   	double emplace(const_iterator position, size_t quantity, const double value);

	   	double erase(const_iterator position);

	   	void push_back(const double value);
	   	void  pop_back();

	   	void push_front(const double value);
	   	void  pop_front();	   	

		void clear() noexcept;
		void swap(const_iterator position_1, const_iterator position_2)  noexcept;

	private: 

		size_t cur_size = 0;
		node*  head     = nullptr;
		node*  tail     = nullptr;
};


//-----------------------------------------------------------------------------

#endif // LIST_HPP_INCLUDED