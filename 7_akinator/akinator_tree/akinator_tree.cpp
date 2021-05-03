
#include "akinator_tree.hpp"

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree() :
	Tree  {AKINATOR_TREE_NAME},
    base_ {DEFAULT_BASE}
{
	assert(this);
}

//-----------------------------------------------------------------------------

AkinatorTree::AkinatorTree(const std::string base) :
    Tree  {AKINATOR_TREE_NAME},
    base_ {base}
{
    assert(this);
}

//-----------------------------------------------------------------------------

AkinatorTree::~AkinatorTree()
{
    assert(this);
}

//-----------------------------------------------------------------------------
