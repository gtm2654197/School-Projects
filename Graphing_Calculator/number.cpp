#include "number.h"

Number::Number(Token old)
{
    setToken(old.TokenString(), old.Type());
}
int Number::getType()
{
    return Type();
}
string Number::getString()
{
    return TokenString();
}

