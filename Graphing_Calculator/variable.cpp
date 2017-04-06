#include "variable.h"

Variable::Variable(Token old)
{
    setToken(old.TokenString(), old.Type());
}
int Variable::getType()
{
    return Type();
}
string Variable::getString()
{
    return TokenString();
}

