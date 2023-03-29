#include "StringFunctions.h"
#include <iostream>
#include <sstream>

void printSymbol(char symbol, unsigned times)
{
    for (size_t i = 0; i < times; i++)
    {
        std::cout << symbol;
    }
}

void castEnd(char* str, unsigned lenStr)
{
    for (size_t i = lenStr - 1; i >= 0; i--)
    {
        if (str[i] != ' ')
        {
            break;
        }
        str[i] = '\0';
    }
}

void castBegin(char* str, unsigned lenStr)
{
    unsigned indexOfFirstChar = 0;
    for (size_t i = 0; i < lenStr; i++)
    {
        if (str[i] != ' ')
        {
            break;
        }
        indexOfFirstChar++;
    }

    for (size_t i = 0; i < lenStr; i++)
    {
        str[i] = str[i + indexOfFirstChar];
        str[i + indexOfFirstChar] = '\0';
    }
}

void castString(char* str)
{
    int lenStr = strlen(str);
    castEnd(str, lenStr);
    castBegin(str, lenStr);

}
