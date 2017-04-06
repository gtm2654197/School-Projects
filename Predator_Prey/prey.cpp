#include "prey.h"

Prey::Prey() : Organism()
{
    setOrganismType("Prey");
}
Prey::Prey(Organism *old) : Organism(old)
{    
}
Prey::~Prey()
{}
void Prey::move(Organism* grid[][MAX_WIDTH], int i, int j)
{
    //Create a vector of Pairs of possible move locations
    vector<Pair<int,int> > PossibleMoves;
    int m, n;
    //cout << "i:" << i << " j:" << j << endl;
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
    //get random index for Possible Moves Vector
    int numPossMoves = PossibleMoves.size();
    IncrLifeCount();
    if(numPossMoves != 0)
    {
        srand(time(NULL));
        int randomMove = rand()%numPossMoves;

        //get new coordinates
        Pair<int,int> MoveChoice = PossibleMoves.at(randomMove);
        int row = MoveChoice.key;
        int col = MoveChoice.value;

        //Copy to new location and delete
        Moved();
        grid[row][col] = new Prey(grid[i][j]);
        delete grid[i][j];
        grid[i][j] = NULL;
    }    
}
void Prey::breed(Organism* grid[][MAX_WIDTH], int i, int j)
{
    if(getBreedCount() >= 4)
    {
        vector<Pair<int,int> > PossibleLocations;
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
                            PossibleLocations.push_back(Pair<int,int>(m,n));
                        }
                    }
                }
            }
        }
        //get random index for Possible Moves Vector
        int numPossLocations = PossibleLocations.size();
        if(numPossLocations != 0)
        {
            srand(time(NULL));
            int randomLocation = rand()%numPossLocations;

            //get new coordinates
            Pair<int,int> LocationChoice = PossibleLocations.at(randomLocation);
            int row = LocationChoice.key;
            int col = LocationChoice.value;

            //Create new Prey at new location
            grid[row][col] = new Prey();
            resetBreedCount();
        }
    }
    else
    {
        IncrBreedCount();
    }

}
void Prey::starve(Organism* grid[][MAX_WIDTH], int i, int j)
{}
