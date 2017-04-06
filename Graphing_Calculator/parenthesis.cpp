#include "parenthesis.h"

Parenthesis::Parenthesis(Token old)
{
    setToken(old.TokenString(), old.Type());
}
int Parenthesis::getType()
{
    return Type();
}
string Parenthesis::getString()
{
    return TokenString();
}
int Parenthesis::getPrecedence()
{
    return 0;
}

