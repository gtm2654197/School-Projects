#ifndef VARIABLE_H
#define VARIABLE_H

#include "token.h"

using namespace std;

class Variable: public Token
{
public:
    Variable(Token old);
    int getType();
    string getString();
};

#endif // VARIABLE_H
