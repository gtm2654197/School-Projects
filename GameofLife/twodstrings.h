#ifndef TWODSTRINGS_H
#define TWODSTRINGS_H


#include <iostream>
#include <iomanip>
#include "mystring.h"

using namespace std;


class TwoDString
{
public:
    TwoDString();

    void Assign(int r, int c, char value);
    char At(int r, int c);
    void Append(int r, char value);
    void Copy(TwoDString& Source, int start, int end);

    void Print(int start, int end);

private:
    String A[100];
};

#endif // TWODSTRINGS_H
