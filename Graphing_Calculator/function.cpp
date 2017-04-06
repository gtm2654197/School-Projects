#include "function.h"

function::function(Token old)
{
    setToken(old.TokenString(), old.Type());
}
int function::getPrecedence()
{
    return 4;
}
int function::getType()
{
    return Type();
}
int function::performOperation(double num, double &result)
{
    string funcString = TokenString();
    if(funcString == "sin")
    {
        result = sin(num);
    }
    if(funcString == "cos")
    {
        result = cos(num);
    }
    if(funcString == "tan")
    {
        result = tan(num);
    }
}
string function::getString()
{
    return TokenString();
}

