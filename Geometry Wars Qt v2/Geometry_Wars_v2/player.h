#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include "constants.h"

using namespace std;

class player
{
public:
    player();                             //Default Constructor
    sf::Sprite& Draw();                   //Returns sprite to draw in window
    sf::Vector2f getPos();                //Returns sprite position
    sf::Vector2f getVelocity();           //Returns sprite velocity

    void move(int x, int y);              //Changes velocity for keyboard inputs
    void joystick_move(float x, float y); //Changes velocity for joystick inputs
    void updatePos();                     //Updates position of sprite based on velocity
    void borderCollision();               //Checks and resolves sprite collision with border
    void reset();                         //Resets player to initial state

    sf::Texture stopped;    //Texture for stopped player
    sf::Texture moving;     //Texture for moving player

private:
    sf::Sprite myPlayer;    //sprite for player class
    sf::Vector2f velocity;  //velocity vector for sprite
};

#endif // PLAYER_H
