
#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "akinator_tree.h"
#include "akinator_settings.h"

//-----------------------------------------------------------------------------

class Akinator
{
    private:

        AkinatorTree* akinator_tree_ = nullptr;

        void call_menu()       const;
        void call_guess_mode() const;

        void add_root() const;

    public:

        Akinator();
        Akinator(const std::string base);
       ~Akinator();

        void launch() const;
        void dump()   const;
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_HPP_INCLUDED