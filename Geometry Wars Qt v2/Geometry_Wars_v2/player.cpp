#include "player.h"

player::player()
{
    moving.loadFromFile("../Geometry_Wars_v2/textures/spaceship_small_moving.png");  //Loads in moving player texture
    stopped.loadFromFile("../Geometry_Wars_v2/textures/spaceship_small.png");        //Loads in stopped player texture
    myPlayer.setTexture(stopped);                                                    //Initializes player texture to stopped
    myPlayer.setPosition(sf::Vector2f(BORDER/2, BORDER/2));                          //player position set to middle of screen
    myPlayer.setOrigin(sf::Vector2f(playerOffset,playerOffset));                     //sets origin to center for transformations
    velocity.x = 0.f;                                                                //set x velocity to 0
    velocity.y = 0.f;                                                                //set y velocity to 0
}
//Returns player sprite to draw in game class
sf::Sprite &player::Draw()
{
    return myPlayer;
}
//Returns player velocity
sf::Vector2f player::getVelocity()
{
    return velocity;
}
//Changes velocity of player from keyboard inputs
void player::move(int x, int y)  //{input,result} = x:{-1,left},{0,none},{1,right} y:{-1,down},{0,none},{1,up}
{
    if(x == 0 && y == 0)
    {
        velocity.x = 0.f;
        velocity.y = 0.f;
    }
    if(x == 1 && y == 0)
    {
        velocity.x = maxVelocity;
        velocity.y = 0.f;
    }
    if(x == -1 && y == 0)
    {
        velocity.x = -maxVelocity;
        velocity.y = 0.f;
    }
    //Diagonal movements unitized and multiplied by maxVelocity scalar
    //so that movement in all directions is same speed
    if(x == 1 && y == 1)
    {
        velocity.x = maxVelocity/sqrtf(2.f);
        velocity.y = -maxVelocity/sqrtf(2.f);
    }
    if(x == -1 && y == -1)
    {
        velocity.x = -maxVelocity/sqrtf(2.f);
        velocity.y = maxVelocity/sqrtf(2.f);
    }
    if(x == 1 && y == -1)
    {
        velocity.x = maxVelocity/sqrtf(2.f);
        velocity.y = maxVelocity/sqrtf(2.f);
    }
    if(x == -1 && y == 1)
    {
        velocity.x = -maxVelocity/sqrtf(2.f);
        velocity.y = -maxVelocity/sqrtf(2.f);
    }
    if(x == 0 && y == 1)
    {
        velocity.x = 0.f;
        velocity.y = -maxVelocity;
    }
    if(x == 0 && y == -1)
    {
        velocity.x = 0.f;
        velocity.y = maxVelocity;
    }
}
//Changes velocity of player based on joystick movements
void player::joystick_move(float x, float y)
{
    float invMagnitude = 1/sqrtf(x*x + y*y);  //Inverse vector magnitude for unitizing
    velocity.x = maxVelocity*invMagnitude*x;  //Unitized x * maxVelocity scalar
    velocity.y = maxVelocity*invMagnitude*y;  //Unitized y * maxVelocity scalar
}
//Updates player position using velocity
void player::updatePos()
{
    myPlayer.move(velocity);                 //Moves player with velocity vector
    if(velocity.x == 0 && velocity.y == 0)   //If 0 velocity, set player texture to stopped
    {
        myPlayer.setTexture(stopped);
    }
    else                                     //Velocity vector != 0
    {
        myPlayer.setTexture(moving);         //Set player texture to moving
        float angle;
        //gets angle to orient player sprite
        if(velocity.y < 0) angle = atan(velocity.x/velocity.y) * -RadtoDeg;
        //resolves arctan domain limits
        else angle = angle = atan(velocity.x/velocity.y) * -RadtoDeg + 180.f;
        //sets rotation to angle
        myPlayer.setRotation(angle);
    }
    borderCollision();                       //Checks and resolves border collision
}
//Returns position of player sprite
sf::Vector2f player::getPos()
{
    return myPlayer.getPosition();
}
//Checks and resolves border collsion
void player::borderCollision()
{
    sf::Vector2f pos = getPos();
    if(pos.x < playerOffset)               //x position left of border
    {
        myPlayer.setPosition(sf::Vector2f(playerOffset,pos.y));
    }
    if(pos.x > (BORDER-playerOffset))      //x position right of border
    {
        myPlayer.setPosition(sf::Vector2f(BORDER-playerOffset,pos.y));
    }
    if(pos.y < playerOffset)               //y position above border
    {
        myPlayer.setPosition(sf::Vector2f(pos.x, playerOffset));
    }
    if(pos.y > (BORDER-playerOffset))      //y position below border
    {
        myPlayer.setPosition(sf::Vector2f(pos.x, BORDER-playerOffset));
    }
    //resolves combinations of x and y out of bounds
    if(pos.x < playerOffset && pos.y < playerOffset)
    {
        myPlayer.setPosition(sf::Vector2f(playerOffset,playerOffset));
    }
    if(pos.x < playerOffset && pos.y > (BORDER-playerOffset))
    {
        myPlayer.setPosition(sf::Vector2f(playerOffset, BORDER-playerOffset));
    }
    if(pos.x > (BORDER-playerOffset) && pos.y < playerOffset)
    {
        myPlayer.setPosition(sf::Vector2f(BORDER-playerOffset,playerOffset));
    }
    if(pos.x > (BORDER-playerOffset) && pos.y > (BORDER-playerOffset))
    {
        myPlayer.setPosition(sf::Vector2f(BORDER-playerOffset,BORDER-playerOffset));
    }
}
//Sets player state to initial value
void player::reset()
{
    myPlayer.setPosition(sf::Vector2f(BORDER/2, BORDER/2));
    velocity.x = 0;
    velocity.y = 0;
}
