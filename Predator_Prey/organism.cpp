#include "organism.h"

Organism::Organism()
{
    lifecount = 0;
    breedcount = 0;
    hungercount = 0;
    Organism_Type = "";
    done = false;
}

Organism::Organism(Organism *old)
{
    lifecount = old->lifecount;
    breedcount = old->breedcount;
    Organism_Type = old->Organism_Type;
    hungercount = old->hungercount;
    done = old->done;
}

Organism::~Organism()
{}

void Organism::move(Organism* grid[][MAX_WIDTH], int i, int j)
{}
void Organism::breed(Organism* grid[][MAX_WIDTH], int i, int j)
{}
void Organism::starve(Organism* grid[][MAX_WIDTH], int i, int j)
{}
void Organism::IncrLifeCount()
{
    lifecount++;
}
void Organism::IncrBreedCount()
{
    breedcount++;
}
void Organism::resetLifeCount()
{
    lifecount = 0;
}
void Organism::resetBreedCount()
{
    breedcount = 0;
}
void Organism::setOrganismType(string Type)
{
    Organism_Type = Type;
}
string Organism::getOrganismType()
{
    return Organism_Type;
}
int Organism::getBreedCount()
{
    return breedcount;
}
void Organism::IncrHungerCount()
{
    hungercount++;
}
void Organism::resetHungerCount()
{
    hungercount = 0;
}
int Organism::getHungerCount()
{
    return hungercount;
}
void Organism::Moved()
{
    done = true;
}
void Organism::resetMoved()
{
    done = false;
}
bool Organism::hasMoved()
{
    return done;
}

