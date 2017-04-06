#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <string.h>
#include "stringfunctions.h"

using namespace std;


class String
{
public:

    //Constructors
    String();
    String(char b[]);
    String(char b);
    String(string s);

    //Accessors and Mutators
    void Assign(char b, int pos);
    void Append(char b);
    void Append(char b[]);
    void Append(String b);
    char At(int pos);



    //Member Functions
    char operator [](int index);
    void operator +=(char b[]);

    void StrCpy(String source);
    int Find(char b, int pos);
    int Find(String b, int pos);
    int Find(char b[], int pos);
    int FindFirstOf(char CharSet[], int pos);
    int FindFirstOf(String CharSet, int pos);
    int FindFirstNotOf(char CharSet[], int pos);
    int FindFirstNotOf(String CharSet, int pos);
    String SubStr(int start, int length);
    void getLine(const String& source);
    int Length();
    bool Empty();
    void Show(int pos);
    void Print(int start, int end);
    string getString();





    //Friend Functions
    friend ostream& operator <<(ostream& outs, const String& PrintMe);
    friend istream& operator >>(istream& ins, String& MakeMe);
    friend bool operator ==(String left, String right);
    friend bool operator >(String left, String right);
    friend bool operator <(String left, String right);
    friend bool operator <=(String left, String right);
    friend bool operator >=(String left, String right);
    friend String operator +(String left, String right);




private:    
    char a[100];
};

#endif // MYSTRING_H
