
#ifndef LIST_ITERATORS_HPP_INCLUDED
#define LIST_ITERATORS_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iterator>
#include <initializer_list>

//-----------------------------------------------------------------------------

class List;

//!

template <typename ValueType>
class ListIterator: public std::iterator <std::input_iterator_tag, ValueType>
{
	friend class List;
		private:
			ListIterator(ValueType* knot);
		public:
			ListIterator(const ListIterator& list);

	bool operator == (ListIterator const& other_list) const;
	bool operator != (ListIterator const& other_list) const;

	private:
		ValueType* knot_;
};

//-----------------------------------------------------------------------------

#endif // LIST_ITERATORS_HPP_INCLUDED