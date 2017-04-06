#ifndef GRAPH_H
#define GRAPH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "calculator.h"
#include "dimensions.h"
#include <vector>

using namespace std;


class Graph
{
public:
    Graph(Calculator* thisCalc);
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();

    void createGraph();


private:
    sf::RenderWindow window;
    sf::View view;
    vector<sf::Vector2f> points;
    Calculator* calc;
    int defaultX;
    int defaultY;
    string infix;
};

#endif // GRAPH_H
