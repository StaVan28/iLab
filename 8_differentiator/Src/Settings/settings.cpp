#include "settings.h"

//--------------------------

namespace Differenciator
{

void TokenDiff::print_data (FILE* dump) const
{
    assert (dump);

    switch (type_)
    {
        case TokenType::NUMB: fprintf (dump, " NUMB -- {%ld}\n" , value_numb_);
                              break;

        case TokenType::VARB: fprintf (dump, " VARB -- {%c}\n"  , value_varb_);
                              break;

        case TokenType::OPER: fprintf (dump, " OPER -- {%c}\n"  , value_oper_);
                              break;

        default:              printf  ("ERROR! Type: %d\n", type_);
                              break;
    }

}

}; // namespace Differenciator