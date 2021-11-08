//--------------------------------------------------

#include "akinator.hpp"

//--------------------------------------------------

Akinator::Akinator (const std::string& path_base) :
    stack_ {"Akinator stack", DFLT_CAPACITY}
{
    assert (this);

    tree_ = new AkinatorTree (path_base);
}

//-------

Akinator::~Akinator ()
{
    assert (this);

    stack_.dump ();

    delete tree_;
}

//-------

void Akinator::select_akinator_mode ()
{
    printf ("Hello, guys!\n"
            "Plz, select mode!\n"
            "1 -- finding items\n"
            "2 -- definition mode\n"
            "0 -- exit\n");

    char human_input[MAX_BUF] = {};

    while (true)
    {
        scanf ("%1s", human_input);

        clear_stdin();

        if (!strcmp (human_input, "1"))
        {
            finding_mode (tree_->get_root());
            return;
        }
        else if (!strcmp (human_input, "2"))
        {
            definition_mode ();
            return;
        }
        else if (!strcmp (human_input, "0"))
        {
            return;
        }
        else 
            printf ("Plz, write \"2\", \"1\" or \"0\"\n");
    }
}

//--------

void Akinator::finding_mode (NodeTree* cur_node)
{
    printf ("Welcome to the finding mode, buddy!\n"
            "Please guess a word.\n");

    while (cur_node != nullptr)
    {
        printf ("You guess a word \"%s\"?\n", cur_node->data_.c_str());

        if (get_yes_no () == AkinatorAnswer::YES)
        {
            if (cur_node->left_ == nullptr)
            {
                printf ("Oue, I know word \"%s\"\n", cur_node->data_.c_str());
                break;
            }

            cur_node = cur_node->left_;
        }
        else
        {
            if (cur_node->right_ == nullptr)
            {
                printf ("Please write a new answer: ");
                std::string   answer_data = get_string ();

                printf ("Please write diff between %s and %s: It is... ", answer_data.c_str(), cur_node->data_.c_str());                
                std::string question_data = get_string ();

                tree_->add_new_answer     (cur_node, answer_data, question_data);
                tree_->fill_akinator_base ();
                break;
            }

            cur_node = cur_node->right_;
        }
    }
}

//--------------------------------------------------

void Akinator::definition_mode ()
{
    printf ("Welcome to the definition mode, buddy!\n"
            "Please guess a word.\n");

    char human_input[MAX_BUF] = {};
    scanf ("%s", human_input);

    bool res_defin = find_definition (human_input, tree_->get_root ());

    if (res_defin)
    {
        printf ("I've found it!\n", human_input);
    
        printf_defin_result (human_input);
    }
    else
    {
        printf ("I don't know word \"%s\"\n", human_input);
    }


}

bool Akinator::find_definition (const char* finder, const NodeTree* cur_node)
{
    assert (cur_node);

    if (!cur_node->left_ && !cur_node->right_)
    {
        if (!strcmp (finder, cur_node->data_.c_str()))
        {
            stack_.push (cur_node);

            return true;
        }
        else
        { 
            return false;
        }
    }

    if (cur_node->left_)
    {
        stack_.push (cur_node);

        if (find_definition (finder, cur_node->left_))
            return true;

        stack_.pop  ();
    }

    if (cur_node->right_)
    {
        stack_.push (cur_node);

        if (find_definition (finder, cur_node->right_))
            return true;

        stack_.pop  ();
    }

    return false;
}

//--------------------------------------------------

void Akinator::printf_defin_result (const char* finder)
{ 
    printf ("\"%s\" is ", finder);

    int stack_cur_size = stack_.get_cur_size();

    if (!stack_cur_size)
    {
        printf ("%s!!!\n\n", finder);
        return;
    }

    for (int i = 0; i < stack_cur_size - 1; i++)
    {
        if (stack_[i]->left_ == stack_[i + 1])
            printf (    "%s, ", stack_[i]->data_.c_str());
        else
            printf ("not %s, ", stack_[i]->data_.c_str());
    }

    printf ("that's all!!!\n\n");
}

//--------------------------------------------------

std::string Akinator::get_string () const
{
    char*  buf  = nullptr;
    size_t size = 0;

    getline (&buf, &size, stdin);

    char* ptr_symb = strchr (buf, '\n');
    if   (ptr_symb != nullptr)
    {
        *ptr_symb = '\0';
    }

    std::string answer_data (buf);

    free (buf);

    return answer_data;
}

//--------------------------------------------------

AkinatorAnswer Akinator::get_yes_no () const
{
    char human_input[MAX_BUF] = {};

    while (true)
    {
        scanf ("%1s", human_input);

        clear_stdin();

        if      (!strcmp(human_input, "y"))
            return AkinatorAnswer::YES;

        else if (!strcmp(human_input, "n"))
            return AkinatorAnswer::NO;
        
        else 
            printf("Plz, write \"y\" or \"n\"\n");
    }
}

//--------------------------------------------------

void Akinator::clear_stdin () const
{
    int symb = 0;

    do
    {
        symb = getchar ();
    }
    while (symb != '\n' && symb != EOF);
}

//--------------------------------------------------

void print_elem (FILE* dump_stack, const NodeTree* value)
{
    if (value)
        fprintf (dump_stack, "\"%s\"", value->data_.c_str());
    else
        fprintf (dump_stack, "\"(nullptr)\"");
}

//!

NodeTree* get_poison (const NodeTree**)
{
    return nullptr;
}

//--------------------------------------------------
