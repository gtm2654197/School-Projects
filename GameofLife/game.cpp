#include "game.h"

game::game()
{
    Initialize();
}

//Process Functions
void game::Initialize()
{
    int i, j;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            grid.Append(i,'.');
        }
    }
}
void game::Random()
{
    int i, RdmR, RdmC;
    for(i = 0; i < 50; i++)
    {
        RdmR = rand()%(MAX-3) + 1;
        RdmC = rand()%(MAX-3) + 1;

        grid.Assign(RdmR,RdmC,'o');
    }
    CompleteBorders();
}
void game::Kill(int r, int c)
{
    grid.Assign(r,c,'.');
}
void game::KillAll()
{
    int i, j;
    for(i = 0; i < MAX; i++)
    {
        for(j = 0; j < MAX; j++)
        {
            grid.Assign(i,j,'.');
        }
    }
}
void game::BringtoLife(int r, int c)
{
    grid.Assign(r,c,'o');
}
int game::CountNeighbors(int r, int c)
{
    int count = 0;
    char temp;

    //Top-Left
    temp = grid.At(r-1,c-1);
    CountIncrease(temp, count);
    //Top
    temp = grid.At(r-1, c);
    CountIncrease(temp, count);
    //Top-Right
    temp = grid.At(r-1, c+1);
    CountIncrease(temp, count);
    //Left
    temp = grid.At(r, c-1);
    CountIncrease(temp, count);
    //Right
    temp = grid.At(r, c+1);
    CountIncrease(temp, count);
    //Bottom-Left
    temp = grid.At(r+1, c-1);
    CountIncrease(temp, count);
    //Bottom
    temp = grid.At(r+1, c);
    CountIncrease(temp, count);
    //Bottom-Right
    temp = grid.At(r+1, c+1);
    CountIncrease(temp, count);

    return count;
}
void game::CompleteBorders()
{
    char temp;
    int i;
    for(i = 1; i < MAX-1; i++)
    {
        //Top Border
        temp = grid.At(MAX-2, i);
        grid.Assign(0,i,temp);
        //Bottom Border
        temp = grid.At(1,i);
        grid.Assign(MAX-1,i,temp);
        //Left Border
        temp = grid.At(i,MAX-2);
        grid.Assign(i,0,temp);
        //Right Border
        temp = grid.At(i,1);
        grid.Assign(i,MAX-1,temp);
    }
    //Top-Left Corner
    temp = grid.At(MAX-2,MAX-2);
    grid.Assign(0,0,temp);
    //Bottom-Left Corner
    temp = grid.At(1,MAX-2);
    grid.Assign(MAX-1,0,temp);
    //Top-Right Corner
    temp = grid.At(MAX-2,1);
    grid.Assign(0,MAX-1,temp);
    //Bottom-Right Corner
    temp = grid.At(1,1);
    grid.Assign(MAX-1,MAX-1,temp);
}
void game::Print()
{
    grid.Print(1,MAX-2);
}

void game::CountIncrease(char temp, int& count)
{
    if(temp == 'o')
    {
        count++;
    }
}

void game::Copy(game &dest)
{
    dest.grid.Copy(grid, 0, MAX);
}

//Menu Functions
void game::Step()
{
    game temp;
    temp.grid.Copy(grid,0,MAX);
    int i, j;

    for(i = 1; i < MAX-1; i++)
    {
        for(j = 1; j < MAX-1; j++)
        {
            int count;
            char cell;
            count = temp.CountNeighbors(i,j);
            cell = temp.At(i,j);
            if(cell == 'o')
            {
                if(count < 2 || count > 3)
                {
                    Kill(i,j);
                }
            }
            else
            {
                if(count == 3)
                {
                    BringtoLife(i,j);
                }
            }
        }
    }
    CompleteBorders();
}

void game::Go()
{
    int i;
    for(i = 0; i < 10; i++)
    {
        Step();
    }
}

void game::SavePattern(string filename, int r1, int c1, int r2, int c2)
{
    filename += ".txt";
    ofstream File;
    File.open(filename.c_str());
    if(File.is_open())
    {
        int i,j;
        for(i = r1; i <= r2; i++)
        {
            for(j = c1; j <= c2; j++)
            {
                File << At(i,j);
            }
            File << 'L';
        }
        File << 'E';
        cout << endl << "File Saved." << endl;
    }
    else
    {
        cout << endl << "Error saving file." << endl;
    }
}
void game::LoadPattern(string filename, int r1, int c1)
{
    filename += ".txt";
    ifstream File;
    string line;
    File.open(filename.c_str());
    if(File.is_open())
    {
        getline(File,line);
        char temp;
        int n, i, j;
        n = 0;
        for(i = r1; line[n] != 'E'; i++)
        {
            for(j = c1; line[n] != 'L'; j++)
            {
                temp = line[n];
                grid.Assign(i,j,temp);
                n++;
            }
            n++;
        }
    }
        CompleteBorders();
}
void game::SaveScreen(string filename)
{
    filename += ".txt";
    ofstream File;
    File.open(filename.c_str());
    if(File.is_open())
    {
        int i,j;
        for(i = 0; i < MAX; i++)
        {
            for(j=0; j < MAX; j++)
            {
                File << At(i,j);
            }
        }
    }
}
void game::LoadScreen(string filename)
{
    filename += ".txt";
    ifstream File;
    File.open(filename.c_str());
    if(File.is_open())
    {
        string line;
        getline(File,line);
        char temp;
        int n,i,j;
        n = 0;
        for(i = 0; i < MAX; i++)
        {
            for(j = 0; j < MAX; j++)
            {
                temp = line[n];
                grid.Assign(i,j,temp);
                n++;
            }
        }
    }
}

void game::Run()
{
    char choice;
    bool exit = false;
    do
    {
        cout << "      S[T]EP    [G]O    [C]LEAR    [R]ANDOM    [S]AVE" << endl
             << "            [L]OAD    [K]ILL  LI[F]E     E[X]IT      " << endl;
        Print();
        cout << ": "; cin >> choice;
        switch(toupper(choice))
        {
            case 'T':
            {
                Step();
                break;
            }
            case 'G':
            {
                Go();
                break;
            }
            case 'C':
            {
                KillAll();
                break;
            }
            case 'R':
            {
                Random();
                break;
            }
            case 'S':
            {
                string filename;
                char menu;
                cout << "1) Save Pattern" << endl
                     << "2) Save Screen"  << endl;
                cin >> menu;
                switch(menu)
                {
                    case '1':
                    {
                        cout << "File Name: ";
                        cin >> filename;
                        int r1, c1, r2, c2;
                        char comma;
                        cout << "First Coordinate (Row, Column): "; cin >> r1 >> comma >> c1;
                        cout << "Second Coordinate(Row, Column): "; cin >> r2 >> comma >> c2;
                        SavePattern(filename, r1,c1,r2,c2);
                        break;
                    }
                    case '2':
                    {
                        cout << "File Name: ";
                        cin >> filename;
                        SaveScreen(filename);
                        break;
                    }
                    default:
                    {
                        cout << "Invalid Input." << endl;
                        break;
                    }
                }
                break;
            }
            case 'L':
            {
                string filename;
                char menu;
                cout << "1) Load Pattern" << endl
                     << "2) Load Screen"  << endl;
                cin >> menu;
                switch(menu)
                {
                    case '1':
                    {
                        cout << "File Name: ";
                        cin >> filename;
                        int r1,c1;
                        char comma;
                        cout << "Coordinate (Row, Column): ";
                        cin >> r1 >> comma >> c1;
                        LoadPattern(filename, r1, c1);
                        break;
                    }
                    case '2':
                    {
                        cout << "File Name: ";
                        cin >> filename;
                        LoadScreen(filename);
                        break;
                    }
                    default:
                    {
                        cout << "Invalid Input." << endl;
                        break;
                    }
                }
                break;
            }
            case 'X':
            {
                exit = true;
                break;
            }
            case 'K':
            {
                int r1, c1;
                char comma;
                cout << "Coordinate (Row, Column): "; cin >> r1 >> comma >> c1;
                Kill(r1,c1);
                break;
            }
            case 'F':
            {
                int r1, c1;
                char comma;
                cout << "Coordinate (Row, Column): "; cin >> r1 >> comma >> c1;
                BringtoLife(r1,c1);
                break;
            }
            default:
            {
                cout << "Invalid Input." << endl;
                break;
            }
        }
    }while(!exit);
}


//Test
char game::At(int r, int c)
{
    char temp;
    temp = grid.At(r,c);
    return temp;
}
