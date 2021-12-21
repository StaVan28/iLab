#include "diff.h"
#include "parsing_text.h"
using namespace Differenciator;

//-----------------------------------------------------------------------------

int main ()
{
/*
    NodeTree n1 (TokenType::OPER, '*');
    NodeTree n2 (TokenType::VARB, 'x');
    NodeTree n3 (TokenType::NUMB,  28);
    NodeTree n4 (TokenType::OPER, '*');
    NodeTree n5 (TokenType::OPER, '*');
    NodeTree n6 (TokenType::VARB, 'x');
    NodeTree n7 (TokenType::NUMB,  28);

    n1.left_   = &n2;
    n1.right_  = &n3;

    n2.parent_ = &n1;
    n3.parent_ = &n1;

    n4.left_   = &n1;
    n4.right_  = &n5;

    n1.parent_ = &n4;
    n5.parent_ = &n4;

    n5.left_   = &n6;
    n5.right_  = &n7;

    n6.parent_ = &n5;
    n7.parent_ = &n5;

    Tree test_tree("name");
    test_tree.root_ = &n4;
    test_tree.dump(Mode::DEBUG, "Txt/dump");

    Diff test_diff;
    NodeTree* dif_node = test_diff.diff (test_tree.root_);

    Tree test_tree_dif("name diff");
    test_tree_dif.root_ = dif_node;
    test_tree_dif.dump(Mode::DEBUG, "Txt/dump_dif");
*/
    TextDiff test_text ("calc.txt");

    return 0;
}

//-----------------------------------------------------------------------------