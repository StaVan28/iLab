#include "akinator.hpp"

// hpp
//
int main ()
{
    Akinator my_akinator;

    try
    {
        my_akinator.select_akinator_mode ();
    }
    catch (const char* err_msg)
    {
        printf ("ERROR! %s\n", err_msg);
    }
    catch (...)
    {
        printf ("UNKNOWN ERROR!");        
    }

    return 0;
}

// void ==> std::size_t num_symbols.
// добавить обраотку нескольких файлов.
// пустое дерево (неизвестно кто).
// одновременно компилить два дампа