
#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "akinator_tree.hpp"
#include "akinator_settings.hpp"

//-----------------------------------------------------------------------------

class Akinator
{
    private:

        AkinatorTree* akinator_tree_ = nullptr;

        void call_menu() const;

    public:

        Akinator();
        Akinator(const std::string base);
       ~Akinator();

        void launch() const;
        void dump()   const;
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_HPP_INCLUDED