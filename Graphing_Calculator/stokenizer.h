#ifndef STOKENIZER_H
#define STOKENIZER_H

#include <iostream>
#include <string.h>
#include <cstring>
#include "token.h"
#include <vector>

using namespace std;

class STokenize
{
public:
    //Constructors
    STokenize();
    STokenize(const string &s);


    //Accessors
    int Pos();
    string GetString(){return _s;}

    //Member Functions
    void MakeCharSet();
    int GetTokenType(char ch);
    Token GetThisToken(int type);
    string NextString();
    Token NextToken();
    bool Fail();
    friend STokenize& operator >>(STokenize& s, Token& t);
    int StrLen();

private:
    string _s;
    int _pos;
    vector<string> charSet;
};

#endif // STOKENIZER_H
