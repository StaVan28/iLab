
# Tree

Project is only available on Linux!

Important! My trees use Graphviz. if you don't have it installed then perhaps it is worth doing it.

    $ sudo apt-get install graphviz [Dedian, Ubuntu, Mint]
    $ sudo pacman -S graphviz       [Manjaro, Arch]

## Installation

Clone the repository. 

    git clone https://github.com/StaVan28/iLab.git

Go to the tree project.

    cd 6_tree

And install

    make install

After this step you can use my tree)

## Example of use 

```C++
    #include "tree.hpp"

    int main()
    {   
        // init Tree with name 
        Tree tree_example("github_example");
        // or
        // With Unknown Name
        Tree tree_example_Unknown_Name();


        // push new data in head of trees
        tree_example.insert("hello");

        // push new data in head of trees
        tree_example.insert("28");

        // delete tree knot with index(0)
        tree_example.remove("28");


        // write dump info in ./txt/dump_tree.txt
        // write beautiful dump with the help Graphviz 
        tree_example.dump();

        // delete all knots
        tree_example.clear();

    }
```
