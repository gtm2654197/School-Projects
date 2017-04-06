#include "mystring.h"

//Constructors
String::String()
{
    a[0] = NULL;
}
String::String(char b[])
{
    ::StrCpy(a, b);
}
String::String(char b)
{
    a[0] = b;
    a[1] = NULL;
}
String::String(string s)
{
    int length = s.length();
    int i;
    for(i = 0; i < length; i++)
    {
        a[i] = s[i];
    }
    a[i] = NULL;
}


//Accessors and Mutators
void String::Assign(char b, int pos)
{
    int length;
    length = StrLen(a);

    if(pos >= 0 && pos < length)
    {
        a[pos] = b;
    }
}
void String::Append(char b)
{
    int length;
    length = StrLen(a);

    a[length] = b;
    a[length + 1] = NULL;
}
void String::Append(char b[])
{
    StrCat(a,b);
}
void String::Append(String b)
{
    StrCat(a, b.a);
}
char String::At(int pos)
{
    int length;
    length = StrLen(a);
    if(pos >= 0 && pos < length)
    {
        return a[pos];
    }
    else
    {
        return NULL;
    }
}



//Member Functions
void String::StrCpy(String source)
{
    ::StrCpy(a, source.a);
}
char String::operator [](int index)
{
    return a[index];
}
void String::operator +=(char b[])
{
    StrCat(a, b);
}

int String::Find(char b, int pos)
{
    int num;
    num = ::Find(a, b, pos);
    return num;
}
int String::Find(char b[], int pos)
{
    int num;
    num = ::Find(a, b, pos);
    return num;
}
int String::Find(String b, int pos)
{
    int num;
    num = ::Find(a, b.a, pos);
    return num;
}
int String::FindFirstOf(char CharSet[], int pos)
{
    int num;
    num = ::FindFirstOf(a, CharSet, pos);
    return num;
}
int String::FindFirstOf(String CharSet, int pos)
{
    int num;
    num = ::FindFirstOf(a, CharSet.a, pos);
    return num;
}
int String::FindFirstNotOf(char CharSet[], int pos)
{
    int num;
    num = ::FindFirstNotOf(a, CharSet, pos);
    return num;
}
int String::FindFirstNotOf(String CharSet, int pos)
{
    int num;
    num = ::FindFirstNotOf(a, CharSet.a, pos);
    return num;
}
String String::SubStr(int start, int length)
{
    char temp[100];
    ::SubStr(a, temp, start, length);
    return String(temp);
}

int String::Length()
{
    int length;
    length = StrLen(a);
    return length;
}
bool String::Empty()
{
    if(a[0] == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void String::Show(int pos)
{
    ::Show(a, pos);
}

void String::Print(int start, int end)
{
    ::Print(a,start,end);
}

//Friend Functions
ostream& operator <<(ostream& outs, const String& PrintMe)
{
    outs << PrintMe.a;
    return outs;
}
istream& operator >>(istream& ins, String& MakeMe)
{
    char temp[100];
    ins >> temp;
    MakeMe = temp;
    return ins;
}
bool operator ==(String left, String right)
{
    int num;
    num = ::StrCmp(left.a, right.a);
    if(num == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator >(String left, String right)
{
    int num;
    num = ::StrCmp(left.a, right.a);
    if(num == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator <(String left, String right)
{
    int num;
    num = ::StrCmp(left.a, right.a);
    if(num == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator <=(String left, String right)
{
    int num;
    num = ::StrCmp(left.a, right.a);
    if(num == -1 || num == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool operator >=(String left, String right)
{
    int num;
    num = ::StrCmp(left.a, right.a);
    if(num == 1 || num == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
String operator +(String left, String right)
{
    char temp[100];
    StrCpy(temp, left.a);
    StrCat(temp, right.a);
    return String(temp);
}
string String::getString()
{
    string temp = a;
    return temp;
}



