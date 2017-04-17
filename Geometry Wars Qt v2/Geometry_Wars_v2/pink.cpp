#include "pink.h"

Pink::Pink()
{
    enemyType = "Pink";
    sprite.setOrigin(sf::Vector2f(enemyOffset,enemyOffset));
    sprite.setPosition(sf::Vector2f(40.f,40.f));
    accel = sf::Vector2f(0.f,0.f);
    accelbyBullet = sf::Vector2f(0.f,0.f);
    velocity = sf::Vector2f(0.f,0.f);
    angle = 0;    
    direction = true;
    dodging = false;
    points = 100;
}

Pink::Pink(sf::Vector2f position, sf::Texture& texture)
{
    enemyType = "Pink";
    velocity = sf::Vector2f(0.f,0.f);
    sprite.setTexture(texture);
    sprite.setPosition(position);
    sprite.setOrigin(sf::Vector2f(enemyOffset,enemyOffset));
    accel = sf::Vector2f(0.f,0.f);
    angle = 0;
    direction = true;
    points = 100;
}

Pink::~Pink()
{

}
