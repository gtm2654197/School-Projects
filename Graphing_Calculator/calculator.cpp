#include "calculator.h"

//Default Constructor
Calculator::Calculator()
{
    infix = "";
    answer = "";
    error = 0;
    isGraph = false;
}

//Returns Precedence of thisToken for use in Shunting Yard
int Calculator::Precedence(Token thisToken)
{
    string thisOperator = thisToken.TokenString();
    if(thisOperator == "+" || thisOperator == "-")
    {
        return 1;
    }
    if(thisOperator == "*" || thisOperator == "/")
    {
        return 2;
    }
    if(thisOperator == "^")
    {
        return 3;
    }
    else
    {
        return 0;
    }
}
//Receives User Input for Infix, and formats input to be readable by shunting yard
void Calculator::setInfix()
{
    cout << ": "; getline(cin, infix);
    int position = 0;
    while(position < infix.length() && infix.find('(', position) != -1)
    {
        position = infix.find('(', position);
        position++;
        infix.insert(position, " ");
    }
    position = 0;
    while(position < infix.length() && infix.find(')', position) != -1)
    {
        position = infix.find(')', position);
        infix.insert(position, " ");
        position+=2;
    }
}
//Sets Infix to string ifx, and formats infix to be readable by shunting yard
void Calculator::setInfix(string ifx)
{
    infix = ifx;
    int position = 0;
    while(position < infix.length() && infix.find('(', position) != -1)
    {
        position = infix.find('(', position);
        position++;
        infix.insert(position, " ");
    }
    position = 0;
    while(position < infix.length() && infix.find(')', position) != -1)
    {
        position = infix.find(')', position);
        infix.insert(position, " ");
        position+=2;
    }
}
//Creates Postfix using Shunting Yard Algorithm
void Calculator::ShuntingYard()
{
    STokenize tokenizer(infix);
    Stack<Token*> OpStack;
    //Tokenize and add to Postfix
    while(!tokenizer.Fail())
    {
        Token thisToken = tokenizer.NextToken();
        int type = thisToken.Type();
        //If type is a number
        if(type == 1)
        {
            postfix.Insert(new Number(thisToken));
        }
        //If type is a parenthesis
        else if(type == 4)
        {            
            if(thisToken.TokenString() == "(")
            {
                OpStack.Push(new Parenthesis(thisToken));
            }
            else if(thisToken.TokenString() == ")")
            {
                while(!OpStack.Empty() && OpStack.Top()->getString() != "(")
                {
                    Token* toPostFix = OpStack.Pop();
                    postfix.Insert(toPostFix);                    
                }                
                OpStack.Pop(); //Delete the (
            }
        }
        //If type is a mathmatical opererator
        else if(type == 3)
        {
            while(!OpStack.Empty() && Precedence(thisToken) <=  OpStack.Top()->getPrecedence())
            {                
                Token* toPostFix = OpStack.Pop();
                postfix.Insert(toPostFix);
            }
            OpStack.Push(new Operator(thisToken));
        }
        //If type is a alphabetic character or series of characters
        else if(type == 0)
        {
            if(thisToken.TokenString() == "X" || thisToken.TokenString() == "x")
            {
                isGraph = true;
                postfix.Insert(new Variable(thisToken));
            }
            else if(thisToken.TokenString() == "sin" || thisToken.TokenString() == "cos" || thisToken.TokenString() == "tan")
            {
                OpStack.Push(new function(thisToken));
            }
        }
       //PrintPostFix();
    }
    //Push what's left of the opstack into the postfix
    while(!OpStack.Empty())
    {        
        postfix.Insert(OpStack.Pop());        
    }
    //PrintPostFix();
}
//Evaluates expressions
void Calculator::EvaluatePostfix()
{
    Stack<double> Result;
    //Error() occurs when a 0 in the denominator is found
    while(!postfix.Empty() && !Error())
    {        
        Token* temp = postfix.Pop();
        //If type is a number, push it to the result stack
        if(temp->getType() == 1)
        {
            string numstring = temp->getString();
            double num = stod(numstring);
            Result.Push(num);
        }
        else
        {
            //If the type is an operator, pop the previous numbers on result stack and perform operation
            if(temp->getType()==3)
            {
                double num1 = Result.Pop();
                double num2 = Result.Pop();
                try
                {
                    double result;
                    temp->performOperation(num1, num2, result);
                    Result.Push(result);
                }
                catch(int)
                {
                    error = 1;
                }
            }
            //If the type is a function, pop previous number from result stack and perform operation
            else if(temp->getType()==0)
            {                
                double num = Result.Pop();
                double result;
                temp->performOperation(num,result);
                Result.Push(result);
            }
        }        
    }
    if(!Error())
    {
        answer = std::to_string(Result.Top());
    }
}
//Evaluates Functions
double Calculator::EvaluateGraph(double x)
{    
    Stack<double> Result;    
    ShuntingYard();    
    //Error() occurs when a 0 in the denominator is found
    while(!postfix.Empty() && !Error())
    {
        Token* temp = postfix.Pop();
        //If type is a number, push it to the result stack
        if(temp->getType() == 1)
        {
            string numstring = temp->getString();
            double num = stod(numstring);
            Result.Push(num);
        }
        else if(temp->getType() == 0)
        {
            //If the type is a function, pop previous number from result stack and perform operation
            if(temp->TokenString() == "sin" || temp->TokenString() == "cos" || temp->TokenString() == "tan")
            {
                double num = Result.Pop();
                double result;
                temp->performOperation(num,result);
                Result.Push(result);
            }
            //If type is a variable, push value x into result stack
            else
            {
                Result.Push(x);
            }
        }
        else
        {
            //If the type is an operator, pop the previous numbers on result stack and perform operation
            if(temp->Type()==3)
            {
                double num1 = Result.Pop();
                double num2 = Result.Pop();
                try
                {
                    double result;
                    temp->performOperation(num1, num2, result);
                    Result.Push(result);
                }
                catch(int)
                {
                    error = 1;
                }
            }            
        }
    }
    if(!Error())
    {
        return Result.Top();
    }
    else
    {
        return 0;
    }
}
string Calculator::getAnswer()
{
    return answer;
}
void Calculator::PrintPostFix()
{    
    node<Token*>* walker = postfix.Copy();
    while(walker->next != NULL)
    {        
        cout << walker->item->TokenString();
        walker = walker->next;
    }
    cout << walker->item->TokenString() << endl;
}
void Calculator::Clear()
{
    if(!postfix.Empty())
    {
        postfix.Clear();
    }
    infix = "";
    isGraph = false;
}
void Calculator::PrintError()
{
    switch(error)
    {
        case 0:
        {
            cout << "No Error";
            break;
        }
        case 1:
        {
            cout << "Undefined";
            break;
        }
    }
}
bool Calculator::Error()
{
    if(error > 0)
    {
        return true;
    }
    return false;
}
void Calculator::PrintAnswer()
{
    if(!Error())
    {
        cout << answer;
    }
    else
    {
        PrintError();
    }
}
void Calculator::PrintInfix()
{
    cout << infix;
}
bool Calculator::checkGraph()
{
    return isGraph;
}
Queue<Token> Calculator::copyPostFix()
{
    Queue<Token> temp;
    node<Token*>* head = postfix.Copy();
    node<Token*>* walker = head;
    while(walker->next != NULL)
    {
        temp.Insert(*(walker->item));
        walker = walker->next;
    }
    temp.Insert(*(walker->item));
    return temp;
}
string Calculator::getInfix()
{
    return infix;
}

