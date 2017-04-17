#include "blue.h"


//Default Constructor
Blue::Blue() : Enemy()
{
    enemyType = "Blue";        
    sprite.setOrigin(sf::Vector2f(enemyOffset,enemyOffset));
    sprite.setPosition(sf::Vector2f(40.f,40.f));
    accel = sf::Vector2f(0.f,0.f);
    accelbyBullet = sf::Vector2f(0.f,0.f);
    velocity = sf::Vector2f(0.f,0.f);
    angle = 0;    
    direction = true;
    dodging = false;
    points = 50;
}
//Constructor recieves position to be spawned and texture by reference
Blue::Blue(sf::Vector2f position, sf::Texture &texture) : Enemy(position, texture)
{
    enemyType = "Blue";
    velocity = sf::Vector2f(0.f,0.f);    
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(sf::Vector2f(enemyOffset,enemyOffset));
    accel = sf::Vector2f(0.f,0.f);
    angle = 0;
    direction = true;
    points = 50;
}
Blue::~Blue()
{

}

