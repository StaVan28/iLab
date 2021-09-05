#ifndef AKINATOR
#define AKINATOR

//--------------------------------------------------

#include "settings.hpp"
#include "tree.hpp"

//--------------------------------------------------

enum class Mode : int
{ 
    finding_mode,
    defining_mode,
};

//--------------------------------------------------

class Akinator
{
    private:

        Mode          mode_;
        AkinatorTree* tree_;

        void select_akinator_mode();

    public:
       
        Akinator();
        Akinator(const std::string path_base);
       ~Akinator();
};

//--------------------------------------------------

#endif //AKINATOR
