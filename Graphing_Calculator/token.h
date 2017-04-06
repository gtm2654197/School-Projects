#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <string.h>

using namespace std;

class Token
{
public:
    Token();
    Token(string s, int type);
    Token(char ch, int type);

    friend std::ostream& operator <<(std::ostream& outs, const Token& t);
    int& Type();
    string TokenString();

    virtual int getPrecedence(){};
    virtual string getString(){};
    virtual int getType(){};
    virtual int performOperation(double num1, double num2, double& result){};
    virtual int performOperation(double num, double &result){};

    void setToken(string TokStr, int TokType);



private:
    string _token;
    int _type;
};

#endif // TOKEN_H
