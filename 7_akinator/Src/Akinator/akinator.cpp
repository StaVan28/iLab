//--------------------------------------------------

#include "akinator.hpp"

//--------------------------------------------------

Akinator::Akinator ()
{
    assert (this);

    tree_ = new AkinatorTree (DEFAULT_PATH_BASE);
    select_akinator_mode ();
}

//-------

Akinator::Akinator (const std::string& path_base)
{
    assert (this);

    tree_ = new AkinatorTree (path_base);
    
    select_akinator_mode ();
}

//-------

Akinator::~Akinator ()
{
    assert (this);

    delete tree_;
}

//-------

void Akinator::select_akinator_mode ()
{
    printf ("Hello, guys!\n"
            "Plz, select mode!\n"
            "1 -- finding items\n"
            "0 -- exit");

    finding_mode ();

    // приветственные слова
    // выбор режима, анализируя ввод человека(выставление режима Mode)
}

//--------

void Akinator::finding_mode ()
{
    AkinatorAnswer answer = get_answer ();

    if (answer == AkinatorAnswer::YES)
    {
        if (cur_node == nullptr)
        {

        }

        tree_->walk (cur_node, TreeDirection::LEFT)
    }

    if (answer == AkinatorAnswer::NO)
    {
        if (cur_node == nullptr)
        {

        }

        tree_->walk (cur_node, TreeDirection::RIGHT)
    }

}

//--------------------------------------------------

AkinatorAnswer Akinator::get_answer () const
{

}

//--------------------------------------------------
