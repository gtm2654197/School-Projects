#include "twodstrings.h"

TwoDString::TwoDString()
{
    Assign(0,0,NULL);
}

void TwoDString::Assign(int r, int c, char value)
{
    A[r].Assign(value, c);
}
char TwoDString::At(int r, int c)
{
    char temp;
    temp = A[r].At(c);
}
void TwoDString::Append(int r, char value)
{
    A[r].Append(value);
}

void TwoDString::Print(int start, int end)
{
    int i, n;
    for(n = start-1; n <= end; n++)
    {
        cout << setw(3);
        cout << n;
    }
    cout << endl;
    for(i = start; i <= end; i++)
    {
        cout << setw(3);
        cout << i;
        A[i].Print(start,end);
        cout << endl;
    }
}

void TwoDString::Copy(TwoDString& Source, int start, int end)
{
    char temp;
    int i, j;
    for(i = start; i < end; i++)
    {
        for(j = start; j < end; j++)
        {
            temp = Source.At(i,j);
            Assign(i,j,temp);
        }
    }
}

