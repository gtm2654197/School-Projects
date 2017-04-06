#ifndef OPERATOR_H
#define OPERATOR_H

#include "token.h"
#include <math.h>

using namespace std;

class Operator: public Token
{
public:
    Operator(Token old);

    int getPrecedence();
    int getType();
    int performOperation(double num1, double num2, double& result);
    string getString();


};

#endif // OPERATOR_H
