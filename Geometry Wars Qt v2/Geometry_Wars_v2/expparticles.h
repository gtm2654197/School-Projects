#ifndef EXPPARTICLES
#define EXPPARTICLES

#include <SFML/Graphics.hpp>
#include <math.h>
#include <cstdlib>

using namespace std;

struct ExpParticles
{
    sf::Vector2f velocity;       //Velocity to move each particle
    sf::RectangleShape particle; //particle sprite
    sf::Clock time;              //used to fade out and delete particle after certain time period
    sf::Text pointValue;         //displays point value of exploded enemy
    int r,g,b,a;                 //values for color
    //Constructor for destroyed enemy types
    ExpParticles(string type, sf::Vector2f pos, float angle, sf::Font &font, int points)
    {
        particle.setSize(sf::Vector2f(3.f, .5f));
        particle.setOrigin(sf::Vector2f(1.5f,.5f));
        particle.setPosition(pos);
        pointValue.setFont(font);
        pointValue.setOrigin(15.f, 15.f);
        pointValue.setPosition(pos);
        pointValue.setCharacterSize(20);
        pointValue.setString(to_string(points));
        a = 255;
        if(type == "Blue")
        {
            r = 0;
            g = 255;
            b = 186;

        }
        if(type == "Purple")
        {
            r = 255;
            g = 0;
            b = 174;
        }
        if(type == "Green")
        {
            r = 0;
            g = 255;
            b = 78;
        }
        if(type == "Pink" || type == "smallPink")
        {
            r = 255;
            g = 135;
            b = 228;
        }
        pointValue.setColor(sf::Color(r,g,b,a));
        particle.setFillColor(sf::Color(r,g,b,a));
        particle.setRotation(angle);
        time.restart();
        float x = cosf(angle);
        float y = sinf(angle);
        float unitize = 1/sqrt(x*x + y*y);
        velocity.x = x*unitize*1.5f;
        velocity.y = y*unitize*1.5f;
    }
    //Constructor for destroyed player
    ExpParticles(sf::Vector2f pos, float angle)
    {
        particle.setSize(sf::Vector2f(3.f, .5f));
        particle.setOrigin(sf::Vector2f(1.5f,.5f));
        particle.setPosition(pos);
        a = 255;
        r = rand()%256;
        g = rand()%256;
        b = rand()%256;
        particle.setFillColor(sf::Color(r,g,b,a));
        particle.setRotation(angle);
        time.restart();
        float x = cosf(angle);
        float y = sinf(angle);
        float unitize = 1/sqrt(x*x + y*y);
        //int randVel = rand()%6;
        float randVel = static_cast<float> (rand())/(static_cast<float> (RAND_MAX/10));
        velocity.x = x*unitize*randVel;
        velocity.y = y*unitize*randVel;
    }
};



#endif // EXPPARTICLES

