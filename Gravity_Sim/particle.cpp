#include "particle.h"
#include <math.h>

Particle::Particle()
{
    circle.setFillColor(sf::Color::White);
    circle.setRadius(0);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    setMass();
    velocityX = 0;
    velocityY = 0;
}

void Particle::setSize(double radius)
{
    circle.setRadius(radius);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    setMass();
}

void Particle::setColor(int color)
{
    switch(color)
    {
        case 0:
        {
            circle.setFillColor(sf::Color::White);
            break;
        }
        case 1:
        {
            circle.setFillColor(sf::Color::Red);
            break;
        }
        case 2:
        {
            circle.setFillColor(sf::Color::Blue);
            break;
        }
        case 3:
        {
            circle.setFillColor(sf::Color::Green);
            break;
        }
        case 4:
        {
            circle.setFillColor(sf::Color::Yellow);
            break;
        }
        case 5:
        {
            circle.setFillColor(sf::Color::Magenta);
            break;
        }
        default:
        {
            circle.setFillColor(sf::Color::Cyan);
            break;
        }
    }
}

void Particle::setPosition(int x, int y)
{
    circle.setPosition(x,y);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
}

void Particle::changeVelocity(double x, double y)
{
    velocityX += x;
    velocityY += y;
}

void Particle::setVelocity(double x, double y)
{
    velocityX = x;
    velocityY = y;
}

double Particle::getVelocityX()
{
    return velocityX;
}

double Particle::getVelocityY()
{
    return velocityY;
}

sf::CircleShape Particle::getCircle()
{
    return circle;
}

void Particle::setMass()
{
    double radius = circle.getRadius();
    double volume = (4/3)*(4*atan(1))*(pow(radius,3));
    mass = pow(volume,1.5);
}

double Particle::getMass()
{
    return mass;
}



