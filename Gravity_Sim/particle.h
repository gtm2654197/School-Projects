#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>


class Particle
{
public:
    Particle();

    void setSize(double radius);
    void setColor(int color);
    void setPosition(int x, int y);
    void changeVelocity(double x, double y);
    void setVelocity(double x, double y);
    double getVelocityX();
    double getVelocityY();
    sf::CircleShape getCircle();
    void setMass();    
    double getMass();


    sf::CircleShape circle;
    double mass;
    double velocityX;
    double velocityY;
};

#endif // PARTICLE_H
