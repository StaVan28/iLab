
#include "akinator_tree.h"

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree() :
    Tree  {AKINATOR_TREE_NAME},
    base_ {DEFAULT_BASE}
{
    assert(this);

    fill_tree();
}

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree(const std::string base) :
    Tree  {AKINATOR_TREE_NAME},
    base_ {base}
{
    assert(this);

    fill_tree();
}

//-----------------------------------------------------------------------------

AkinatorTree::~AkinatorTree()
{
    assert(this);
}

//-----------------------------------------------------------------------------

void AkinatorTree::fill_tree()
{

}

//-----------------------------------------------------------------------------

