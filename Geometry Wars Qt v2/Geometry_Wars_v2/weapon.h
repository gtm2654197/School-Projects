#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>
#include <iostream>

#include "constants.h"

using namespace std;

class Weapon
{
public:
    //Default Constructor
    Weapon();
    //Constructor used for all weapon types
    Weapon(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture);

    sf::Sprite& Draw();                            //Returns sprite to draw to window
    sf::Vector2f& getVelocity();                   //Returns velocity vector
    sf::Vector2f getPosition();                    //Returns position vector
    bool borderCollision();                        //Returns true for bullet collision with border
    bool enemyCollision(sf::Vector2f& enemyPos);   //Returns true for bullet collision with enemy
    void updatePos();                              //Updates position of bullet sprite using velocity
protected:
    sf::Sprite bullet;      //Weapon sprite
    sf::Vector2f velocity;  //Velocity vector of sprite
};

#endif // WEAPON_H
