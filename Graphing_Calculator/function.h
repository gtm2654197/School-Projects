#ifndef FUNCTION_H
#define FUNCTION_H

#include "token.h"
#include <math.h>

class function: public Token
{
public:
    function(Token old);

    int getPrecedence();
    int getType();
    int performOperation(double num, double &result);
    string getString();
};

#endif // FUNCTION_H
