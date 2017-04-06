 #include "stringfunctions.h"
#include <iostream>
#include <iomanip>

using namespace std;

//StrLen takes a character array and returns it's length
int StrLen(char a[])
{
    int i = 0;
    for(i = 0; a[i] != NULL; i++){}
    return i;
}

//StrCopy copies the source array to the dest array until a
//NULL character is found in the source array
void StrCpy(char dest[], char source[])
{
    int i = 0;
    for(i = 0; source[i] != NULL; i++)
    {
        dest[i] = source[i];
    }
    dest[i] = NULL;    
}

//StrCat appends the source array to the dest array by
//copying source array to the end of dest array
void StrCat(char dest[], char source[])
{
    int destlength, sourcelength;
    destlength = StrLen(dest);
    sourcelength = StrLen(source);
    int j = 0;
    int i = 0;

    for(i = destlength; i < (destlength + sourcelength); i++)
    {
        dest[i] = source[j];
        j++;
    }
    dest[i] = NULL;
}

//Compares array a and b, returns 0 if all same
//returns -1 if first character in a to differ to b
//is less than the character in b
//returns 1 if the first character in a a to differ
//to b is greater than the character in b
int StrCmp(char a[], char b[])
{
    int i = 0;
    int n;
    for(i = 0; a[i] != NULL && a[i] == b[i]; i++);
    if(a[i] == b[i])
    {
        n = 0;
    }
    if(a[i] > b[i])
    {
        n = 1;
    }
    if(a[i] < b[i])
    {
        n = -1;
    }
    return n;
}


//StrChr returns first postion of character b in array a
//return -1 if b is not found in array a
int StrChr(char a[], char b)
{
    int n;
    n = Find(a, b, 0);
    return n;
}

//StrRChr returns last position of character b in array a
//returns -1 if b is not found in array a
int StrRChr(char a[], char b)
{
    int i;
    int n;
    n = StrLen(a);
    for(i = n-1; i >= 0 && a[i] != b; i--);
    return i;
}

//StrNCpy copies N characters from the source array to
//the dest array
void StrNCpy(char dest[], char source[], int N)
{
    int i = 0;
    for(i = 0; i < N && source[i] != NULL; i++)
    {
        dest[i] = source[i];
    }
    dest[i] = NULL;
}

//StrNCat appends N characters from the source array to
//the dest array or until the source array reaches a NULL
void StrNCat(char dest[], char source[], int N)
{
    int destlength, sourcelength;
    destlength = StrLen(dest);
    sourcelength = StrLen(source);
    int j = 0;
    int i = 0;

    for(i = destlength; (i < (destlength+N)) && (source[j] != NULL); i++)
    {
        dest[i] = source[j];
        j++;
    }
    dest[i] = NULL;
}

//Compares N characters from dest array to source
//array. Returns -1 if first character to differ
//in source is less than the character in dest.
//Returns 0 if they are the same. Returns 1 if
//first character to differ in source is greater
//than character in dest.
int StrNCmp(char dest[], char source[], int N)
{
    char sourcetemp[N];
    char desttemp[N];
    StrNCpy(sourcetemp, source, N);
    StrNCpy(desttemp, dest, N);
    int i;
    i = StrCmp(sourcetemp, desttemp);
    return i;
}

//Searches for the first instance of b in array a
//starting and position pos, and returns the index
//of that instance. Returns -1 if b is not found
//in array a.
int Find(char a[], char b, int pos)
{
    int i = 0;
    for(i = pos; (a[i] != NULL) && (a[i] != b); i++);
    if(a[i] == b)
    {
        return i;
    }
    else
    {
        return -1;
    }
}

//Searches for first instance of array b as a whole
//in array a starting at postion pos. Returns the index
//of that instance. Returns -1 if array b is not found in
//array a.
int Find(char a[], char b[], int pos)
{
    int i;
    int n;
    int stop = 1;
    n = StrLen(b);

    for(i = 0; a[i] != NULL && stop != 0; i++)
    {
        char temp[n];
        SubStr(a, temp, i, n);
        stop = StrCmp(temp,b);
    }

    if(stop == 0)
    {
        return i-1;
    }
    else
    {
        return -1;
    }

}

//Reverses order of array a
void Reverse(char a[])
{
    int i = 0;
    int j = 0;
    int n = 0;
    for(i = 0; a[i] != NULL; i++);
    char temp[i];
    temp[i] = NULL;
    i--;
    for(j = i; j >= 0; j--)
    {
        temp[j] = a[n];
        n++;
    }
    StrCpy(a, temp);
}

//FindFirstOf returns the position of the first instance where a member of
//the key array equals a member of the source array, starting from source
//position pos
int FindFirstOf(char source[], char key[], int pos)
{    
    int i = 0;
    int n = -1;

    for(i = 0; (source[i] != NULL) && (n == -1); i++)
    {
        n = Find(key, source[i], 0);
    }

    if(source[i] == NULL)
    {
        return -1;
    }
    else
    {
        return i-1;
    }
}

//FindFirstNotOf returns the position of the first instance where a member
//of the key array does not equal a member of the source array, starting
//from source position pos
int FindFirstNotOf(char source[], char key[], int pos)
{
    int i = 0;
    int n = 0;


    for(i = pos; n != -1; i++)
    {
        n = Find(key, source[i], 0);        
    }    
    return i-1;
}


//Copies source array from position pos for length N to
//dest array or until source array equals null character
void SubStr(char source[], char dest[], int pos, int N)
{
    int i = 0;
    int j = 0;
    for(i = pos; (i < pos + N) && (source[i] != NULL); i++)
    {
        dest[j] = source[i];
        j++;
    }
    dest[N] = NULL;
}

bool isGT(char a[], char b[])
{
    int n;
    n = StrCmp(a, b);
    if(n == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool isLT(char a[], char b[])
{
    int n;
    n = StrCmp(a, b);
    if(n == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
bool isEQ(char a[], char b[])
{
    int n;
    n = StrCmp(a, b);
    if(n == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//Changes any upper case character to its lower case form
void toLower(char a[])
{
    int i = 0;
    for(i = 0; a[i] != NULL; i++)
    {
        if(a[i] > 64)
        {
            if(a[i] < 91)
            {
                a[i] += 32;
            }
        }
    }
}

//Changes any lower case character to its upper case form
void toUpper(char a[])
{
    int i = 0;
    for(i = 0; a[i] != NULL; i++)
    {
        if(a[i] > 96)
        {
            if(a[i] < 123)
            {
                a[i] -= 32;
            }
        }
    }
}

void Print(char a[], int start, int end)
{
    int i;
    for(i = start; i <= end || a[i] == NULL; i++)
    {
        cout << setw(3);
        cout << a[i];
    }
}

//Test Functions

//Shows position pos with arrow under array a
void Show(char a[], int pos)
{
    cout << a << endl;
    int i = 0;
    for(i = 0; i < pos; i++)
    {
        cout << ".";
    }
    if(pos >= 0)
    {
        cout << '^';
    }
}

//Tests StrLen, StrCpy, StrCat, StrCmp, StrChr,
//StrRChr, StrNCpy, StrNCat, StrNCmp
void TestStrFunc()
{
    const int MAX = 100;
    int pos;
    char a[MAX] = "abcdef";
    char b[MAX] = "123456";
    char c[MAX] = "abc123";
    char d[MAX];

    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "c: " << c << endl;

    cout << "----Test StrLen----" << endl;
    cout << "Length of a(" << a << "): " << StrLen(a);
    cout << endl << endl;

    cout << "----Test StrCpy----" << endl;
    cout << "Copy a(" << a << ") to d: ";
    StrCpy(d, a);
    cout << d << endl << endl;

    cout << "----Test StrCat----" << endl;
    cout << "Concatenate a(" << a << ") to b(" << b << "): ";
    StrCat(b, a);
    cout << b << endl << endl;

    cout << "----Test StrCmp----" << endl;
    cout << "Compare a(" << a << ") to c(" << c << "): " << StrCmp(a, c) << endl;
    cout << "Compare a(" << a << ") to d(" << d << "): " << StrCmp(a, d) << endl;
    cout << "Compare a(" << a << ") to 'abcefg': " << StrCmp(a, "abcefg");
    cout << endl << endl;

    cout << "----Test StrChr----" << endl;

    cout << "Return position of 'c' in 'abcdef': " << endl;
    pos = StrChr("abcdef", 'c');
    Show("abcdef", pos);
    cout << endl << endl;

    cout << "Return position of '1' in 'abcdef': " << StrChr("abcdef", '1');
    cout << endl << endl;

    cout << "----Test StrRChr----" << endl;

    cout << "Return position of 'c' in '123c123c123': " << endl;
    pos = StrRChr("123c123c123", 'c');
    Show("123c123c123", pos);
    cout << endl << endl;

    cout << "Return position of '1' in 'abcdef': " << StrRChr("abcdef", '1');
    cout << endl << endl;

    cout << "----Test StrNCpy----" << endl;

    cout << "Copy First 4 Characters of 'abcdefg' to d: ";
    StrNCpy(d, "abcdefg", 4);
    cout << d << endl << endl;

    cout << "Copy First 7 Characters of 'abcde' to d: ";
    StrNCpy(d, "abcde", 7);
    cout << d << endl << endl;

    cout << "----Test StrNCat----" << endl;
    StrCpy(b, "123456");
    cout << "Concatenate 4 Characters of a(" << a <<") to b(" << b <<"): ";
    StrNCat(b, a, 4);
    cout << b << endl << endl;

    StrCpy(b, "123456");
    cout << "Concatenate 8 Characters of a(" << a <<") to b(" << b <<"): ";
    StrNCat(b, a, 8);
    cout << b << endl << endl;

    cout << "----Test StrNCmp----" << endl;

    cout << "Compare 3 charcters of 'abcdef' to 'abcd': " << StrNCmp("abcd", "abcdef", 3) << endl;
    cout << "Compare 5 charcters of 'abcdef' to 'abcd': " << StrNCmp("abcd", "abcdef", 5) << endl;
    cout << "Compare 3 charcters of 'abde' to 'abcdef': " << StrNCmp("abde", "abcdef", 3) << endl;
    cout << "Compare 10 charcters of 'abcd' to 'abcdef': " << StrNCmp("abcd", "abcdef", 10) << endl;
}

//Tests Find(a[],b,pos), Find(a[],b[],pos),
//FindFirstOf, FindFirstNotOf
void TestFind()
{
    char ALPHA[100] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char DIGITS[100] = "0123456789";
    char SYMBOLS[100] = " !@#$%^&*()_-+={[}]|\:;\"'?/>.<,~`";

    char address[100] = "1042 S. Holly Ave. Apt #3";

    cout << "----Test Find(a[], b, n)----" << endl;
    cout << "Find 'H' in '" << address << "': " << endl;
    Show(address, Find(address, 'H', 0));
    cout << endl << endl;

    cout << "Find 'z' in '" << address << "': " << Find(address, 'z', 0);
    cout << endl << endl;

    cout << "----Test Find(a[], b[], n)----" << endl;
    cout << "Find 'Ave' in '" << address << "': " << endl;
    Show(address, Find(address, "Ave", 0));
    cout << endl << endl;

    cout << "Find 'abcd' in '" << address << "': " << Find(address, "abcd", 0);
    cout << endl << endl;

    cout << "----Test FindFirstOf----" << endl;
    cout << "Find first instance of alphabet in '" << address << "': " << endl;
    Show(address, FindFirstOf(address, ALPHA, 0));
    cout << endl << endl;

    cout << "Find first instance of a number in '" << address << "': " << endl;
    Show(address, FindFirstOf(address, DIGITS, 0));
    cout << endl << endl;

    cout << "Find first instance of special character in '" << address << "': " << endl;
    Show(address, FindFirstOf(address, SYMBOLS, 0));
    cout << endl << endl;


    cout << "----Test FindFirstNotOf----" << endl;
    cout << "Find first instance of non-number in '" << address << "': " << endl;
    Show(address, FindFirstNotOf(address, DIGITS, 0));
    cout << endl << endl;

    cout << "Find first instance of non-alphabet in '" << address << "': " << endl;
    Show(address, FindFirstNotOf(address, ALPHA, 0));
    cout << endl << endl;
}

//Tests SubStr
void TestSubStr()
{
    char temp1[100];
    char temp2[100];
    char test[100] = "abcd1234";

    cout << "----Test SubStr----" << endl;
    cout << "4 characters from " << test << " from position 2: ";
    SubStr(test, temp1, 2, 4);
    cout << temp1 << endl << endl;

    cout << "4 characters from " << test << " from position 7: ";
    SubStr(test, temp2, 7, 4);
    cout << temp2 << endl << endl;
}

//Tests isGT, isLT, isEQ
void TestBool()
{
    char test1[100] = "ABCD";
    char test2[100] = "EFGH";
    char test3[100] = "ABCD";
    bool result;

    cout << "----Test isGT----" << endl;
    cout << "Is '" << test1 << "' greater than '" << test2 << "'? ";
    result = isGT(test1, test2);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }

    cout << "Is '" << test2 << "' greater than '" << test1 << "'? ";
    result = isGT(test2, test1);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }

    cout << "----Test isLT----" << endl;
    cout << "Is '" << test1 << "' less than '" << test2 << "'? ";
    result = isLT(test1, test2);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }

    cout << "Is '" << test2 << "' less than '" << test1 << "'? ";
    result = isLT(test2, test1);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }

    cout << "----Test isEQ----" << endl;
    cout << "Is '" << test1 << "' equal to '" << test2 << "'? ";
    result = isEQ(test1, test2);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }

    cout << "Is '" << test1 << "' equal to '" << test3 << "'? ";
    result = isEQ(test1, test3);
    if(result)
    {
        cout << "TRUE" << endl << endl;
    }
    else
    {
        cout << "FALSE" << endl << endl;
    }
}

//Tests toUpper
void TesttoUpper()
{
    char test1[100] = "abcdef";
    char test2[100] = "a1b3kj";
    char test3[100] = "ABCdEF";

    cout << "----Test toUpper----" << endl;

    cout << test1 << " to upper: ";
    toUpper(test1); cout << test1 << endl << endl;

    cout << test2 << " to upper: ";
    toUpper(test2); cout << test2 << endl << endl;

    cout << test3 << " to upper: ";
    toUpper(test3); cout << test3 << endl << endl;
}

//Tests toLower
void TesttoLower()
{
    char test1[100] = "ABCDEF";
    char test2[100] = "A1B2B3";
    char test3[100] = "abcDef";

    cout << "----Test toLower----" << endl;

    cout << test1 << " to lower: ";
    toLower(test1); cout << test1 << endl << endl;

    cout << test2 << " to lower: ";
    toLower(test2); cout << test2 << endl << endl;

    cout << test3 << " to lower: ";
    toLower(test3); cout << test3 << endl << endl;
}

//Tests Reverse
void TestReverse()
{
    char test[100] = "abcde12345";

    cout << "----Test Reverse----" << endl;

    cout << test << " in reverse: ";
    Reverse(test); cout << test << endl << endl;
}


