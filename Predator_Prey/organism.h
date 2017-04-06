#ifndef ORGANISM_H
#define ORGANISM_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "pair.h"
#include <vector>
#include "dimensions.h"

using namespace std;

class Organism
{
public:
    Organism();
    Organism(Organism* old);
    virtual ~Organism();
    virtual void move(Organism* grid[][MAX_WIDTH], int i, int j);
    virtual void breed(Organism* grid[][MAX_WIDTH], int i, int j);
    virtual void starve(Organism* grid[][MAX_WIDTH], int i, int j);
    void IncrLifeCount();
    void IncrBreedCount();
    void resetLifeCount();
    void resetBreedCount();
    int getBreedCount();
    void IncrHungerCount();
    void resetHungerCount();
    int getHungerCount();
    void setOrganismType(string Type);
    string getOrganismType();
    void Moved();
    void resetMoved();
    bool hasMoved();


private:
    int lifecount;
    int breedcount;
    int hungercount;
    bool done; //set when object is moved, reset at end of step
    string Organism_Type;
};

#endif // ORGANISM_H
