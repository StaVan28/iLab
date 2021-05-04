
#include "akinator.hpp"

//-----------------------------------------------------------------------------

Akinator::Akinator()
{
	assert(this);
    akinator_tree_ = new AkinatorTree(DEFAULT_BASE);
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

    while (true) 
    {
        int human_input = 0;
        std::cin >> human_input;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(ALL_BUFFER, '\n');
            std::cout << "Incorect input. Plz repeat!" << std::endl;
        }
        else 
        {
            std::cin.ignore(ALL_BUFFER, '\n');
            
            switch(human_input)
            {
                case Guess_mode: call_guess_mode();
                                 return;

                default:         std::cout << "Incorect input. Plz repeat!" << std::endl;
                                 continue;
            }
        }
    }
}

//-----------------------------------------------------------------------------

void Akinator::call_guess_mode() const
{
    if (akinator_tree_.empty())
    {
        // rewrite
        return;
    }
}

//-----------------------------------------------------------------------------
