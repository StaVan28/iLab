
# Lists

This my first C++ proj, don't judge strictly)
Project is only available on Linux!

Important! My lists use Graphviz. if you don't have it installed then perhaps it is worth doing it.

    $ sudo apt-get install graphviz [Dedian, Ubuntu, Mint]
    $ sudo pacman -S graphviz       [Manjaro, Arch]

## Installation

Clone the repository. 

    git clone https://github.com/StaVan28/iLab.git

Go to the List project.

    cd 5_list

And install

    make install

After this step you can use my lists)

## Example of use 

```C++
    #include "list.h"

    int main()
    {   
        // init List with template 
        List<double> list_example("github_example");
        // or
        // With Unknown Name
        List<int> list_example_Unknown_Name();


        // push new data in head of lists
        list_example.push_head(28);

        // push new data in tail of lists
        list_example.push_tail(29.28);

        // delete list knot with index(0)
        list_example.erase(1);

        // push BEFORE index(0) new data(6)
        list_example.insert(position::BEFORE, 0, 6);

        // push AFTER index(1) new data(54)
        list_example.insert(position::AFTER, 1, 54);

        // delete list in tail 
        list_example.pop_tail();

        // delete list in head
        list_example.pop_head();

        // write dump info in ./txt/dump_list.txt
        // upgrade with dump info ./txt/log_list.txt
        // write beautiful dump with the help Graphviz 
        list_example.dump();

        // delete all knots
        list_example.clear();

    }
```

    
