#ifndef PREDATOR_H
#define PREDATOR_H

#include <iostream>
#include "organism.h"

using namespace std;

class Predator: public Organism
{
public:    
    Predator();
    Predator(Organism* old);
    ~Predator();
    void move(Organism* grid[][MAX_WIDTH], int i, int j);
    void breed(Organism* grid[][MAX_WIDTH], int i, int j);
    void starve(Organism* grid[][MAX_WIDTH], int i, int j);

};

#endif // PREDATOR_H
