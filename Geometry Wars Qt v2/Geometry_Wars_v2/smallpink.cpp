#include "smallpink.h"

smallPink::smallPink()
{
    enemyType = "smallPink";
    sprite.setOrigin(sf::Vector2f(6.f,6.f));
    sprite.setPosition(sf::Vector2f(40.f,40.f));
    accel = sf::Vector2f(0.f,0.f);
    accelbyBullet = sf::Vector2f(0.f,0.f);
    velocity = sf::Vector2f(0.f,0.f);
    angle = 0;    
    direction = true;
    dodging = false;
    points = 50;
}

smallPink::smallPink(sf::Vector2f position, sf::Texture& texture)
{
    enemyType = "smallPink";
    velocity = sf::Vector2f(0.f,0.f);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(enemyOffset,enemyOffset));
    sprite.setPosition(position);
    randVelocity();
    accel = sf::Vector2f(0.f,0.f);
    angle = 0;
    direction = true;
    points = 50;
}

smallPink::~smallPink()
{

}
//Assigns random velocity vector upon spawn
void smallPink::randVelocity()
{
    srand(time(0));
    int randX = rand()%100;
    int randY = rand()%100;
    float x = 0.f+randX;
    float y = 0.f+randY;    
    float unitize = 1/sqrt(x*x+y*y);
    velocity.x = x*unitize*maxsmallPinkVel;
    velocity.y = y*unitize*maxsmallPinkVel;
}
//Assigns random position within acceptable radius of position
void smallPink::Spawn(sf::Vector2f position)
{
    float leftX = position.x - 100.f;
    float rightX = position.x + 100.f;
    float topY = position.y - 100.f;
    float bottomY = position.y + 100.f;
    if(leftX < enemyOffset) leftX = enemyOffset;
    if(rightX > BORDER - enemyOffset) rightX = BORDER - enemyOffset;
    if(topY < enemyOffset) topY = enemyOffset;
    if(bottomY > BORDER - enemyOffset) bottomY = BORDER - enemyOffset;
    int rangeX = rightX - leftX;
    int rangeY = bottomY - topY;
    float x = rand()%rangeX + leftX;
    float y = rand()%rangeY + topY;
    sprite.setPosition(sf::Vector2f(x,y));
}
