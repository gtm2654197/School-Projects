#include "stokenizer.h"

STokenize::STokenize()
{    
    _s = "";
    _pos = 0;
    MakeCharSet();
}

STokenize::STokenize(const string& s)
{
   _s = s;
   _pos = 0;
   MakeCharSet();
}


void STokenize::MakeCharSet()
{
    string Alphabetic = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string Numeric = "0123456789.";
    string Punctuation = "!,:;'\"?";
    string Math = "%^*+=-/";
    string Parenthesis = "()";
    string White_Space = " ";
    string End_of_Line = "\n";
    string Special = "@#$&_][}{|~`><";

    charSet.push_back(Alphabetic);
    charSet.push_back(Numeric);
    charSet.push_back(Punctuation);
    charSet.push_back(Math);
    charSet.push_back(Parenthesis);
    charSet.push_back(White_Space);
    charSet.push_back(End_of_Line);
    charSet.push_back(Special);
}

int STokenize::GetTokenType(char ch)
{
    /* Types:
     * 0) Alphabetic
     * 1) Numeric
     * 2) Punctuation
     * 3) Math
     * 4) Parenthesis
     * 5) White Space
     * 6) End-of-Line
     * 7) Special Characters
     */
    int i;
    int pos = -1;
    for(i = 0; pos == -1 && i < 7; i++)
    {
        string temp = charSet[i];
        pos = temp.find(ch,0);
    }
    return i-1;
}

Token STokenize::GetThisToken(int type)
{
    string temp;
    int end;
    end = _s.find_first_not_of(charSet[type], _pos);
    int difference = end - _pos;
    if(end == _s.length()+1)
    {
        difference--;
        temp = _s.substr(_pos, difference);
    }
    else
    {
        temp = _s.substr(_pos, difference);
    }
    _pos = end;
    Token newToken(temp, type);
    return newToken;
}

string STokenize::NextString()
{

}

Token STokenize::NextToken()
{
    char temp;
    int type;
    Token newToken;
    temp = _s.at(_pos);
    type = GetTokenType(temp);
    newToken = GetThisToken(type);
    return newToken;
}

bool STokenize::Fail()
{
//    char* cstr = new char[_s.length()+1];
//    std::strcpy(cstr, _s.c_str());
    if(_pos == -1)
    {        
        return true;
    }
    else
    {        
        return false;
    }
}

int STokenize::Pos()
{
    return _pos;
}

STokenize& operator >>(STokenize& s, Token& t)
{

}

int STokenize::StrLen()
{
    return _s.length();
}


