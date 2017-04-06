#ifndef SIMULATION_H
#define SIMULATION_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "particle.h"



class Simulation
{
public:
    Simulation();
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();

    int mouseCollision(float mouseX, float mouseY);
    int particleCollision(int particle1, int particle2);
    void particleAbsorb(int bigParticle, int smallParticle);

    std :: vector<Particle> particles;

private:
    sf::RenderWindow window;
//    int zoomX;
//    int zoomY;
//    sf::View view;
};

#endif // SIMULATION_H
