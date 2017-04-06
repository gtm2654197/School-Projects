#ifndef NUMBER_H
#define NUMBER_H

#include "token.h"

class Number: public Token
{
public:
    Number(Token old);
    int getType();
    string getString();
};

#endif // NUMBER_H
