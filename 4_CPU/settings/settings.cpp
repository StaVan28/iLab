
#include "CPU.h"

//-----------------------------------------------------------------

//@ if you use size function don't remember освободить указатель 
char* concat(const char* file_path, const char* tag, const char* source)
{
    assert(file_path);
    assert(source   );

    if (tag == nullptr) 
    {
        size_t len_file_path = strlen(file_path);
        size_t len_source    = strlen(source   );

        char* result = (char*) calloc(len_file_path           + len_source + 1, sizeof(char));
        assert(result);
     
        memcpy(result                          , file_path, len_file_path    );
        memcpy(result+ len_file_path           , source   , len_source    + 1);    

        return result;
    }
    else 
    {
        size_t len_file_path = strlen(file_path);
        size_t len_tag       = strlen(tag      );
        size_t len_source    = strlen(source   );

        char* result = (char*) calloc(len_file_path + len_tag + len_source + 1, sizeof(char));
        assert(result);

           memcpy(result                          , file_path, len_file_path    );
        memcpy(result + len_file_path          , tag      , len_tag            );
        memcpy(result + len_file_path + len_tag, source   , len_source    + 1);

        return result;
    }
}

//-----------------------------------------------------------------

FILE* fopen_file_with_path(const char* file_path, const char* tag, const char* source, const char* mode)
{
    char* all_file_path = concat(file_path, tag, source);

    FILE* file_name = fopen(all_file_path, mode);
    assert(file_name);

    free(all_file_path);
    all_file_path = nullptr;

    return file_name;
}

//-----------------------------------------------------------------

double is_different(double value_1, double value_2)
{
    if (fabs(value_1 - value_2) > EPSILON)
        return value_1 - value_2;
    else
        return false;
}

//-----------------------------------------------------------------
