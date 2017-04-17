#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "constants.h"

using namespace std;

class Enemy
{
public:    
    //Constructors
    Enemy();
    //Constructor takes in enemy texture and position to spawn
    Enemy(sf::Vector2f position, sf::Texture& texture);
    //Destructor
    ~Enemy();
    //Returns sprite to draw to window
    sf::Sprite& Draw();
    //Moves sprite in with acceleration toward player
    void updatePos(sf::Vector2f playerPos);
    //Set position of sprite
    void setPosition(sf::Vector2f pos);
    //Checks and resolves border collision for purple enemy
    void borderCollisionPurple();
    //border collision for "following" enemies
    void borderCollision();
    //Returns position of sprite as vector
    sf::Vector2f getPos();
    //returns point value of enemy
    int getPoints(){return points;}
    //Returns enemy type as string
    string getType();
    //Used by "following" enemies, uses current inertia and acceleration towards player
    void followPlayer(sf::Vector2f playerPos, float maxVel, float acceleration);
    //Resolves the unique dodging feature of green enemies
    void greenUpdate(sf::Vector2f bulletPos);
    //Checks if green enemy needs to dodge based on bullet distance
    bool bulletinRadius(sf::Vector2f bulletPos);
    //Checks for collision with other enemy units to avoid bunching up
    void enemyCollision(sf::Vector2f enemyPos);
    //returns color of sprite, used for setting explosion color
    sf::Color getColor();

protected:
    sf::Vector2f accel;          //current acceleration of enemy toward player
    sf::Vector2f accelbyBullet;  //acceleration applied to green by bullet
    sf::Vector2f velocity;       //velocity vector used to move sprite
    sf::Sprite sprite;           //enemy sprite
    string enemyType;            //string identifying enemy type
    int angle;                   //angle of rotation
    int points;                  //point value of enemy
    bool direction;              //used to change direction of rotation
    bool dodging;                //checks to see if green is currently dodging
};

#endif // ENEMY_H
