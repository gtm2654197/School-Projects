#include "purple.h"

Purple::Purple()
{
    enemyType = "Purple";
    sprite.setOrigin(sf::Vector2f(20.f,20.f));
    sprite.setPosition(sf::Vector2f(40.f,40.f));
    accel = sf::Vector2f(0.f,0.f);
    accelbyBullet = sf::Vector2f(0.f,0.f);
    velocity = sf::Vector2f(0.f,0.f);
    angle = 0;    
    direction = true;    
    dodging = false;
    points = 25;
}

Purple::Purple(sf::Vector2f position, sf::Texture& texture)
{
    enemyType = "Purple";
    randomVector();
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(sf::Vector2f(20.f,20.f));
    accel = sf::Vector2f(0.f,0.f);
    angle = 0;
    direction = true;
    points = 25;
}

Purple::~Purple()
{

}
//Assigns random velocity vector upon purple spawn
void Purple::randomVector()
{
    srand(time(0));
    float x = rand()%100;
    float y = rand()%100;
    float invMagnitude = 1/sqrt(x*x + y*y);
    velocity.x = x*invMagnitude*maxPurpleVel;
    velocity.y = y*invMagnitude*maxPurpleVel;
}
