#include "syntactic_analysis.h"
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

    BufNodes test_buf_nodes (DEFAULT_SOURCE_TEXT, START_MAX_NODES);

    return 0;
}

//-----------------------------------------------------------------------------


/* !TODO
    VVV1) вынести очевидный нью (в списки инициализации) 
    VVV2) замнить fseek () -> fstat ()
    3) норм обработка ошибок
    VVV4) заменить num_of_tokens на max_of_tokens
    VVV5) заменить token на node
    VVV6) пересмотр структуры проекты (пернос глобальных структур в diff)
    VVV7) num_symbols_of_file -- наглядная смена класса(!)

    8.1) сделать обертку на выд ресурсами
    8.2) не брать ресурс до места исключения
    8.3) try/catch
    8.4) перегруженный без опрератор исключения new (при аллоцирование сложных классов 
    с конструктрукторами не защищает от выюроса их исключения)
    8.5) unique_ptr/написать сам

    9)  двойное опредление лексемы в create_buffer_tokens()
    VVV10) удалить ручками конструкторы копирования операторы присваивания и тд
*/