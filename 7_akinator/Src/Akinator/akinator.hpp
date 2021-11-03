#ifndef AKINATOR
#define AKINATOR

//--------------------------------------------------

#include "settings.hpp"
#include "tree.hpp"

//--------------------------------------------------

enum class AkinatorMode : int
{ 
     FINDING_MODE,
    DEFINING_MODE,
};

//!

enum class AkinatorAnswer : int
{
    YES,
    NO,
};

//--------------------------------------------------

class Akinator
{
    private:

        AkinatorMode  mode_;
        AkinatorTree* tree_;

        void select_akinator_mode ();
        
        AkinatorAnswer get_yes_no  () const;
        std::string    get_string  () const;
        void           clear_stdin () const;

        void finding_mode (NodeTree* root);

    public:
       
        Akinator ();
        Akinator (const std::string& path_base);
       ~Akinator ();
};

//--------------------------------------------------

#endif //AKINATOR
