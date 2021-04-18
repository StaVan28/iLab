
#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include <iostream> 
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

using namespace std;

#include "settings.h"

//-----------------------------------------------------------------------------

template <typename Data_t>
struct Node {
    Data_t        data_ = 0;
    Node<Data_t>* prev_ = nullptr;
    Node<Data_t>* next_ = nullptr;
};

//-----------------------------------------------------------------------------

template <typename Data_t>
class List {

    public:

        // constructors
        List();
        List(const char* const name);

        List(const List&) = delete;

        // distructor
       ~List();

        // operators
        const List& operator = (const List&) = delete;

        // capacities
        bool empty() const noexcept;
        int   size() const noexcept;

        //! methods
        void   push_head(const Data_t data);
        Data_t  pop_head();

        void   push_tail(const Data_t data);
        Data_t  pop_tail();

        void   insert(position indx_pos, const int indx, const Data_t data); 
        Data_t  erase(const int indx);
        
        void dump();

        void clear();

    private:

        int   size_ = 0;
        char* name_ = STRING_POISON;

        Node<Data_t>* head_ = nullptr;
        Node<Data_t>* tail_ = nullptr;

        Node<Data_t>* search_node(const int indx) const noexcept;

        void graph() const noexcept;
        void log();

        void print_form(ofstream& my_stream);

        int begin() const noexcept;
        int   end() const noexcept;
};

//-----------------------------------------------------------------------------

#include "list.hpp"

//-----------------------------------------------------------------------------

#endif // LIST_HPP_INCLUDED