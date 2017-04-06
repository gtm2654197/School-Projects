#include "simulation.h"

Simulation::Simulation()
{
    Initialize();
}
void Simulation::Initialize()
{
    //Initialize grid
    int i, j;
    for(i = 0; i < (MAX_HEIGHT); i++)
    {
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            grid[i][j] = NULL;
        }
    }
    //Seed Rand function & Initialize Variables
    srand(time(NULL));
    int PredCount = 0;
    int PreyCount = 0;
    int numPred = ((MAX_HEIGHT)*(MAX_WIDTH))/(25);
    int numPrey = ((MAX_HEIGHT)*(MAX_WIDTH))/(12);
//    int numPred = 0;
//    int numPrey = 5;

    //Create numPred Predators in grid
    while(PredCount < numPred)
    {        
        int i = rand()%(MAX_HEIGHT-1);
        int j = rand()%(MAX_WIDTH-1);
        if(grid[i][j] == NULL)
        {
            grid[i][j] = new Predator;
            PredCount++;            
        }
    }    

    //Create numPrey Prey in grid    
    while(PreyCount < numPrey)
    {        
        int i = rand()%(MAX_HEIGHT-2)+1;
        int j = rand()%(MAX_WIDTH-2)+1;
        if(grid[i][j] == NULL)
        {
            //cout << "i:" << i << " j:" << j << endl;
            grid[i][j] = new Prey;
            PreyCount++;            
        }
    }

}
void Simulation::Step()
{
    int i, j;

    //Perform Predator Functions First
    for(i = 0; i < (MAX_HEIGHT); i++)
    {
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getOrganismType() == "Predator" && grid[i][j]->hasMoved() != true)
                {                    
                    grid[i][j]->move(grid, i, j);                    
                }
            }
        }
    }    

    //Perform Prey Functions
    for(i = 1; i < (MAX_HEIGHT); i++)
    {
        for(j = 1; j < (MAX_WIDTH); j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getOrganismType() == "Prey" && grid[i][j]->hasMoved() != true)
                {                    
                    grid[i][j]->move(grid, i, j);                    
                }
            }
        }
    }
    //Reset Moved
    for(i = 0; i < (MAX_HEIGHT); i++)
    {
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            if(grid[i][j] != NULL)
            {
                grid[i][j]->resetMoved();
            }
        }
    }
    //Starve Predators
    for(i = 0; i < (MAX_HEIGHT); i++)
    {
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getOrganismType() == "Predator")
                {
                    grid[i][j]->starve(grid, i, j);
                }
            }
        }
    }
    //Breed Predators and Prey
    for(i = 0; i < (MAX_HEIGHT); i++)
    {
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            if(grid[i][j] != NULL)
            {
                if(grid[i][j]->getOrganismType() == "Predator")
                {                    
                    grid[i][j]->breed(grid, i, j);
                }
                if(grid[i][j]->getOrganismType() == "Prey")
                {                    
                    grid[i][j]->breed(grid, i, j);
                }
            }
        }
    }
}
void Simulation::Go()
{

}
void Simulation::Draw()
{

}

void Simulation::Print()
{
    int i, j;
    for(i = 0; i < (MAX_HEIGHT); i++)
    {        
        for(j = 0; j < (MAX_WIDTH); j++)
        {
            cout << setw(2);
            if(grid[i][j] == NULL)
            {
                cout << " ";
            }
            else if(grid[i][j]->getOrganismType() == "Prey")
            {
                cout << "O";
            }
            else if(grid[i][j]->getOrganismType() == "Predator")
            {
                cout << "X";
            }
            else
            {
                cout << "?";
            }
        }
        cout << endl;
    }
}

