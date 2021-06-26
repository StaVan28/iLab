
#ifndef AKINATOR_HPP_INCLUDED
#define AKINATOR_HPP_INCLUDED

//-----------------------------------------------------------------------------

#include "akinator_settings.h"
#include "akinator_tree.h"

//-----------------------------------------------------------------------------

class Akinator
{
    private:

        AkinatorTree* akinator_tree_ = nullptr;

        void call_main_menu()  const;
        void call_guess_mode() const;

    public:

        Akinator();
        Akinator(const std::string base);
       ~Akinator();

       void launch() const;
};

//-----------------------------------------------------------------------------

#endif // AKINATOR_HPP_INCLUDED