#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "stokenizer.h"
#include "token.h"
#include "operator.h"
#include "parenthesis.h"
#include "number.h"
#include "variable.h"
#include "function.h"
#include "node.h"
#include "queue.h"
#include "mystack.h"

using namespace std;

class Calculator
{
public:
    Calculator();
    int Precedence(Token thisToken);
    void setInfix();
    void setInfix(string ifx);
    void ShuntingYard();
    void EvaluatePostfix();
    double EvaluateGraph(double x);
    string getAnswer();
    void PrintPostFix();
    void Clear();
    void PrintError();
    bool Error();
    bool checkGraph();    \
    void PrintAnswer();
    void PrintInfix();
    string getInfix();
    Queue<Token> copyPostFix();


private:
    string infix;
    Queue<Token*> postfix;
    string answer;   
    int error;
    bool isGraph;
};

#endif // CALCULATOR_H
