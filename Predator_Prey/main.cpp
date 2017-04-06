#include <iostream>
#include "simulation.h"

using namespace std;

int main()
{
    Simulation sim;
    bool exit = false;
    sim.Print();
    while(!exit)
    {
        cout << endl << endl;
        char choice;
        cout << "[S]tep   e[X]it" << endl;
        cout << ":"; cin >> choice;
        switch(toupper(choice))
        {
            case 'S':
            {
                sim.Step();
                sim.Print();
                break;
            }
            case 'X':
            {
                exit = true;
                break;
            }
            default:
            {
                sim.Print();
                break;
            }
        }
    }
    cout << endl << endl << endl;
    return 0;
}

