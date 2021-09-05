//--------------------------------------------------

#include "tree.hpp"
#include "parsing_text.hpp"

//--------------------------------------------------

AkinatorTree::AkinatorTree() :
    path_base_ {DEFAULT_PATH_BASE}
{
    assert(this);
    // распарсинг базы, заполнение по дереву 
}

//---------

AkinatorTree::AkinatorTree(const std::string path_base) :
    path_base_ {path_base}
{
    assert(this);

}

//---------

AkinatorTree::~AkinatorTree()
{
    assert(this);
    // удаление дерева
}

//---------

void AkinatorTree::fill_akinator_tree()
{
    Text parser_base(path_base_);
}

//---------

void AkinatorTree::fill_akinator_base()
{

}

//--------------------------------------------------
