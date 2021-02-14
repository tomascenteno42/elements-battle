#include "../main.h"

/* UTILS */

bool stringIsNumeric(std::string s)
{
    for (int i = 0; i < s.length(); i ++)
    {
        if ((int)s[i] < 48 || (int)s[i] > 57)
            return false;
    }
    return true;
}

bool dataIsInVector(std::vector<int> vector, int data)
{
    for (int i = 0; i < vector.size(); i ++)
    {
        if (vector[i] == data)
            return true;
    }
    return false;
}