
#include "akinator_tree.h"

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree() :
    Tree  {AKINATOR_TREE_NAME},
    base_ {DEFAULT_BASE}
{
    assert(this);

    fill_tree(DEFAULT_BASE);
}

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree(const std::string base) :
    Tree  {AKINATOR_TREE_NAME},
    base_ {base}
{
    assert(this);

    fill_tree(base);
}

//-----------------------------------------------------------------------------

AkinatorTree::~AkinatorTree()
{
    assert(this);
}

//-----------------------------------------------------------------------------

void AkinatorTree::fill_tree(const std::string base)
{
    FILE* read_file = fopen(base.c_str(), "rb");
    assert(read_file);

    

    fclose(read_file);
}

//-----------------------------------------------------------------------------

