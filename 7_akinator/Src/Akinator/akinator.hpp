#ifndef AKINATOR
#define AKINATOR

//--------------------------------------------------

#include "settings.hpp"
#include "tree.hpp"
#include "stack.h"

//--------------------------------------------------

enum class AkinatorAnswer : int
{
    YES,
    NO,
};

//--------------------------------------------------

class Akinator
{
    private:
        
        AkinatorTree*          tree_;
        Stack<const NodeTree*> stack_; 

        AkinatorAnswer get_yes_no  () const;
        std::string    get_string  () const;
        void           clear_stdin () const;

        void    finding_mode (NodeTree* root);

        void definition_mode     ();
        bool find_definition     (const char* finder, const NodeTree* root);
        void printf_defin_result (const char* finder);

    public:
       
        Akinator (const std::string& path_base = DEFAULT_PATH_BASE);
       ~Akinator ();

        void select_akinator_mode ();
};

//!

void      print_elem (FILE* dump_stack, const NodeTree* value);

NodeTree* get_poison (const NodeTree**);

//--------------------------------------------------

#endif //AKINATOR
