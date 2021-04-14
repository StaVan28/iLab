
#ifndef LIST_ITERATORS_HPP_INCLUDED
#define LIST_ITERATORS_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iterator>
#include <initializer_list>

//-----------------------------------------------------------------------------

class List;

//!

template <typename value_type>
class List_iterator: public std::iterator <std::input_iterator_tag, value_type>
{
	friend class List;
		private:
			List_iterator(value_type* knot);
		public:
			List_iterator(const List_iterator& knot);

	private:
   		value_type* knot;
};

//-----------------------------------------------------------------------------

#endif // LIST_ITERATORS_HPP_INCLUDED