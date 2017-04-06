#include "token.h"

/* Types:
 * 0) Alphabetic
 * 1) Numeric
 * 2) Punctuation
 * 3) Math
 * 4) White Space
 * 5) End-of-Line
 * 6) Special Characters
 */

Token::Token()
{
    _token = "";
    _type = 0;
}

Token::Token(string s, int type)
{
   _token = s;
   _type = type;
}

Token::Token(char ch, int type)
{
    _token = ch;
    _type = type;
}

std::ostream& operator <<(std::ostream& outs, const Token& t)
{
    outs << "{[" << t._token << "]" << " " << t._type << "}";
    return outs;
}

int& Token::Type()
{
    return _type;
}

string Token::TokenString()
{
    return _token;
}

void Token::setToken(string TokStr, int TokType)
{
    _token = TokStr;
    _type = TokType;
}

