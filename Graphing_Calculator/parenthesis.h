#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "token.h"
using namespace std;

class Parenthesis: public Token
{
public:
    Parenthesis(Token old);
    int getType();
    string getString();
    int getPrecedence();
};

#endif // PARENTHESIS_H
