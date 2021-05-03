
#include "akinator.hpp"

//-----------------------------------------------------------------------------

Akinator::Akinator()
{
	assert(this);
    akinator_tree_ = new AkinatorTree();
}

//-----------------------------------------------------------------------------

Akinator::Akinator(const std::string base)
{
	assert(this);
    akinator_tree_ = new AkinatorTree(base);
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
    call_menu();
}

//-----------------------------------------------------------------------------

void Akinator::call_menu() const
{
    std::cout << std::endl
              << "Hello, I'm Akinator, I know everything in the world!" << std::endl
              << "Choose a operating mode!" << std::endl 
              << std::endl 
              << "1) Object guess" << std::endl;

    int human_input = 0;
    std::cin  >> human_input;
}

//-----------------------------------------------------------------------------

