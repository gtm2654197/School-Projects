#include "predator.h"

Predator::Predator() : Organism()
{    
    setOrganismType("Predator");
}

Predator::Predator(Organism *old) : Organism(old)
{
}

Predator::~Predator()
{

}

void Predator::move(Organism* grid[][MAX_WIDTH], int i, int j)
{    
    vector<Pair<int, int> > EmptySpaces;
    vector<Pair<int, int> > PreySpaces;
    int m, n;    
    for(m = i-1; m < i+2; m++)
    {
        for(n = j-1; n < j+2; n++)
        {            
            //doesn't check it's own position
            if(!(m == i && n == j))
            {                
                //check that m and n are within grid borders
                if(m < MAX_HEIGHT && m > -1 && n < MAX_WIDTH && n > -1)
                {
                    //Assign all available empty spaces to EmptySpaces Vector
                    if(grid[m][n] == NULL)
                    {                        
                        EmptySpaces.push_back(Pair<int,int>(m,n));
                    }
                    //Assign all available Prey to PreySpaces vector
                    else if(grid[m][n]->getOrganismType() == "Prey")
                    {                        
                        PreySpaces.push_back(Pair<int,int>(m,n));                        
                    }
                }
            }
        }
    }    
    //if there are empty spaces but no prey spaces
    if(EmptySpaces.size() > 0 && PreySpaces.size() == 0)
    {
        //Get random index of an available empty space
        int PossibleMoves = EmptySpaces.size();
        srand(time(NULL));
        int randomMove = rand()%PossibleMoves;

        //Access new coordinates from pair in vector
        Pair<int,int> MoveChoice = EmptySpaces.at(randomMove);
        int row = MoveChoice.key;
        int col = MoveChoice.value;

        //Copy to new location and delete
        IncrHungerCount();
        IncrLifeCount();
        Moved();
        grid[row][col] = new Predator(grid[i][j]);
        delete grid[i][j];
        grid[i][j] = NULL;
    }
    //if there are prey available
    else if(PreySpaces.size() > 0)
    {
        //Get random index of an available prey in prey spaces
        int PossibleMoves = PreySpaces.size();
        srand(time(NULL));
        int randomMove = rand()%PossibleMoves;

        //Access new coordinates from pair in vector
        Pair<int,int> MoveChoice = PreySpaces.at(randomMove);
        int row = MoveChoice.key;
        int col = MoveChoice.value;

        //Delete Prey, Copy to new location, reset hunger count, delete old
        delete grid[row][col];
        resetHungerCount();
        IncrLifeCount();
        Moved();
        grid[row][col] = new Predator(grid[i][j]);        
        delete grid[i][j];
        grid[i][j] = NULL;
    }
    else
    {
        IncrHungerCount();
        IncrLifeCount();
    }
}
void Predator::breed(Organism* grid[][MAX_WIDTH], int i, int j)
{
    if(getBreedCount() >= 7)
    {
        vector<Pair<int,int> > PossibleMoves;
        int m, n;
        for(m = i-1; m < i+2; m++)
        {
            for(n = j-1; n < j+2; n++)
            {
                //doesn't check it's own position
                if(!(m == i && n == j))
                {
                    //check that m and n are within grid borders
                    if(m < MAX_HEIGHT && m > -1 && n < MAX_WIDTH && n > -1)
                    {
                        if(grid[m][n] == NULL)
                        {
                            PossibleMoves.push_back(Pair<int,int>(m,n));
                        }
                    }
                }
            }
        }
        //get random index for possible breed locations
        int numAvailable = PossibleMoves.size();
        if(numAvailable != 0)
        {            
            srand(time(NULL));
            int randomMove = rand()%numAvailable;

            //get coordinates for random index
            Pair<int,int> BreedChoice = PossibleMoves.at(randomMove);
            int row = BreedChoice.key;
            int col = BreedChoice.value;

            //Create new Predator and reset breed count
            grid[row][col] = new Predator();
            resetBreedCount();
        }
        else
        {           
            IncrBreedCount();
        }
    }
    else
    {
        IncrBreedCount();
    }
}
void Predator::starve(Organism* grid[][MAX_WIDTH], int i, int j)
{
    if(getHungerCount() > 3)
    {
        delete grid[i][j];
        grid[i][j] = NULL;
    }
}

