
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

#include "settings.hpp"

//-----------------------------------------------------------------------------

struct node {
    double data_ = 0;
    node*  prev_ = NODE_POISON;
    node*  next_ = NODE_POISON;
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
        double  pop_head();

        void   push_tail(const double data);
        double  pop_tail();

        void   insert(position indx_pos, const int indx, const double data); 
        double erase(const int indx);
        
        void dump();

        void clear();

    private: 
        int   size_ = 0;
        node* head_ =   NODE_POISON;
        node* tail_ =   NODE_POISON;
        char* name_ = STRING_POISON;

        node* search_node(const int indx) const noexcept;

        void graph() const noexcept;
        void log();
        void print_form(ofstream& my_stream);

        int begin() const noexcept;
        int end()   const noexcept;
};


//-----------------------------------------------------------------------------

#endif // LIST_HPP_INCLUDED