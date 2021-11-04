#ifndef AKINATOR
#define AKINATOR

//--------------------------------------------------

#include "settings.hpp"
#include "tree.hpp"
#include "stack.h"

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
        
        AkinatorTree*    tree_;
        Stack<NodeTree*> stack_; 

        void select_akinator_mode ();
        
        AkinatorAnswer get_yes_no  () const;
        std::string    get_string  () const;
        void           clear_stdin () const;

        void    finding_mode (NodeTree* root);

        void definition_mode ();
        void definition_mode (const char* finder, const NodeTree* root);

    public:
       
        Akinator ();
        Akinator (const std::string& path_base);
       ~Akinator ();
};

//!

void      print_elem (FILE* dump_stack, NodeTree* value);

NodeTree* get_poison (NodeTree**);

//--------------------------------------------------

#endif //AKINATOR
