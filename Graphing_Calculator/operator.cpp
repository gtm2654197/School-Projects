#include "operator.h"

Operator::Operator(Token old)
{
    setToken(old.TokenString(), old.Type());
}

int Operator::getPrecedence()
{
    string thisOperator = TokenString();
    if(thisOperator == "+" || thisOperator == "-")
    {
        return 1;
    }
    if(thisOperator == "*" || thisOperator == "/")
    {
        return 2;
    }
    if(thisOperator == "^")
    {
        return 3;
    }
    else
    {
        return 0;
    }
}
int Operator::getType()
{    
    return Type();
}
int Operator::performOperation(double num1, double num2, double &result)
{
    string operString = TokenString();
    char oper = operString[0];    
    switch(oper)
    {
        case '+':
        {
            result = num2 + num1;
            break;
        }
        case '-':
        {
            result = num2 - num1;
            break;
        }
        case '*':
        {
            result = num2 * num1;
            break;
        }
        case '/':
        {
            if(num1 == 0)
            {
                throw 0;
            }
            result = num2 / num1;
            break;
        }
        case '^':
        {
            result = pow(num2, num1);
            break;
        }
    }
    return result;
}
string Operator::getString()
{
    return TokenString();
}
