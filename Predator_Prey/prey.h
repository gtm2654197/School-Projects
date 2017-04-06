#ifndef PREY_H
#define PREY_H

#include "organism.h"

class Prey: public Organism
{
public:
    Prey();
    Prey(Organism *old);
    ~Prey();
    void move(Organism* grid[][MAX_WIDTH], int i, int j);
    void breed(Organism* grid[][MAX_WIDTH], int i, int j);
    void starve(Organism* grid[][MAX_WIDTH], int i, int j);
};

#endif // PREY_H
