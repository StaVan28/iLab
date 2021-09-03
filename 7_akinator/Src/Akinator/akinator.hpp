#ifndef AKINATOR
#define AKINATOR

//--------------------------------------------------

#include "settings.hpp"

//--------------------------------------------------

enum class akinator_mode : int
{ //&&&&&&&&&&&&&&&&&&
    defined;
}

//--------------------------------------------------

class Akinator
{
    private:

        akinator_mode mode_;

        void select_akinator_mode();

    public:
       
        Akinator();
       ~Akinator();

};

//--------------------------------------------------

#endif //AKINATOR
