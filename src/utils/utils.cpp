#include "../main.h"

/* UTILS */

bool stringIsNumeric(std::string s)
{
    for (int i = 0; i < (s.length() - 1); i ++)
    {
        if ((int)s[i] >= 10)
            return false;
    }
    return true;
}