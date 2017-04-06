#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "twodstrings.h"
#include <string.h>


using namespace std;

class game
{
public:
    //Constructor
    game();

    //Process Functions
    void Initialize();
    void Random();
    void Kill(int r, int c);
    void KillAll();
    void BringtoLife(int r, int c);
    int CountNeighbors(int r, int c);
    void CompleteBorders();
    void Print();
    void CountIncrease(char temp, int& count);
    void Copy(game& dest);
    void Run();

    //Menu Functions
    void Step();
    void Go();
    void SavePattern(string filename, int r1, int c1, int r2, int c2);
    void LoadPattern(string filename, int r1, int c1);
    void SaveScreen(string filename);
    void LoadScreen(string filename);


    //Test
    char At(int r, int c);


private:
    TwoDString grid;
    const int MAX = 20;
};

#endif // GAME_H
