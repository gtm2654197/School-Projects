#ifndef STRINGFUNCTIONS_H
#define STRINGFUNCTIONS_H


int StrLen(char a[]);
void StrCpy(char dest[], char source[]);
void StrCat(char dest[], char source[]);
int StrCmp(char a[], char b[]);
int StrChr(char a[], char b);
int StrRChr(char a[], char b);
void StrNCpy(char dest[], char source[], int N);
void StrNCat(char dest[], char source[], int N);
int StrNCmp(char dest[], char source[], int N);
int Find(char a[], char b, int pos);
int Find(char a[], char b[], int pos);
void Reverse(char a[]);
int FindFirstOf(char source[], char key[], int pos);
int FindFirstNotOf(char source[], char key[], int pos);
void SubStr(char source[], char dest[], int pos, int N);
bool isGT(char a[], char b[]);
bool isLT(char a[], char b[]);
bool isEQ(char a[], char b[]);
void toLower(char a[]);
void toUpper(char a[]);
void Print(char a[], int start, int end);


//Test functions
void Show(char a[], int pos);
void TestStrFunc();
void TestFind();
void TestSubStr();
void TestBool();
void TesttoUpper();
void TesttoLower();
void TestReverse();


#endif // STRINGFUNCTIONS_H
