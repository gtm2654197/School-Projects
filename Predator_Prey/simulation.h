#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <iomanip>
#include "predator.h"
#include "prey.h"
#include "dimensions.h"

using namespace std;

class Simulation
{
public:
    Simulation();
    void Initialize();
    void Step();
    void Go();
    void Draw();    
    void Print();

private:
    Organism* grid[MAX_HEIGHT][MAX_WIDTH];    
};

#endif // SIMULATION_H
