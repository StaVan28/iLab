
#include "list_iterators.hpp"

//-----------------------------------------------------------------------------

template <typename ValueType>
ListIterator<ValueType>::ListIterator(ValueType* knot) :
	knot_(knot)
{

}

//-----------------------------------------------------------------------------

template <typename ValueType>
ListIterator<ValueType>::ListIterator(const ListIterator& list) :
	knot_(list.knot_)
{

}

//-----------------------------------------------------------------------------

template <typename ValueType>
bool ListIterator<ValueType>::operator == (ListIterator const& other_list) const
{
	return knot_.data == other_list.knot_.data;
}

//-----------------------------------------------------------------------------

template <typename ValueType>
bool ListIterator<ValueType>::operator != (ListIterator const& other_list) const
{
	return knot_.data != other_list.knot_.data;
}
