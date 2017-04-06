#include "calculator.h"
#include "graph.h"


using namespace std;

int main()
{
    while(true)
    {
        Calculator* calc = new Calculator;
        calc->setInfix();
        calc->ShuntingYard();
        if(calc->checkGraph())
        {
            Graph* graph = new Graph(calc);
            graph->run();
            calc->Clear();
        }
        else
        {
            calc->EvaluatePostfix();
            calc->PrintAnswer();
            cout << endl;
            calc->Clear();
        }
    }

    return 0;
}


