//--------------------------------------------------

#include "akinator.hpp"

//--------------------------------------------------

Akinator::Akinator()
{
    assert(this);

    tree_ = new AkinatorTree(DEFAULT_PATH_BASE);
    select_akinator_mode();
}

//-------

Akinator::Akinator(const std::string path_base)
{
    assert(this);
    assert(path_base.c_str());

    tree_ = new AkinatorTree(path_base);
    select_akinator_mode();
}

//-------

Akinator::~Akinator()
{
    assert(this);

    delete(tree_);
}

//-------

void Akinator::select_akinator_mode()
{
    // приветственные слова
    // выбор режима, анализируя ввод человека(выставление режима Mode)
}

//--------------------------------------------------
