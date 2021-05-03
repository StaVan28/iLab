
#include "akinator.hpp"

//-----------------------------------------------------------------------------

Akinator::Akinator()
{
	assert(this);
    akinator_tree_ = new AkinatorTree;
}

//-----------------------------------------------------------------------------

Akinator::Akinator(const std::string base)
{
	assert(this);
    akinator_tree_ = new AkinatorTree;
}

//-----------------------------------------------------------------------------

Akinator::~Akinator()
{
    assert(this);
    delete akinator_tree_;
}

//-----------------------------------------------------------------------------

void Akinator::launch() const
{
	assert(this);
}

//-----------------------------------------------------------------------------
