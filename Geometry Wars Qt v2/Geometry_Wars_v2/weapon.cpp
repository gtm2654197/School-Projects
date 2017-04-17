#include "weapon.h"

//Constructors handled by child classes, Weapon class should not be initialized
Weapon::Weapon()
{    

}

Weapon::Weapon(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture)
{

}
//Returns weapon sprite to draw to window
sf::Sprite &Weapon::Draw()
{
    return bullet;
}
//Returns velocity vector
sf::Vector2f& Weapon::getVelocity()
{
    return velocity;
}
//Return position of bullet sprite
sf::Vector2f Weapon::getPosition()
{
    return bullet.getPosition();
}

//Returns true for border collision, to be handled by game class
bool Weapon::borderCollision()
{
    sf::Vector2f bulletPos = bullet.getPosition();
    if(bulletPos.x < bulletOffset)
    {
        return true;
    }
    if(bulletPos.x > BORDER-bulletOffset)
    {
        return true;
    }
    if(bulletPos.y < bulletOffset)
    {
        return true;
    }
    if(bulletPos.y > BORDER-bulletOffset)
    {
        return true;
    }
    return false;
}
//Returns true for enemy collision, to be handled by game class
bool Weapon::enemyCollision(sf::Vector2f& enemyPos)
{
     sf::Vector2f bulletPos = bullet.getPosition();
     float TRx = bulletPos.x + bulletOffset, TRy = bulletPos.y - bulletOffset;  //Top-Right corner of bullet
     float BRx = bulletPos.x + bulletOffset, BRy = bulletPos.y + bulletOffset;  //Bottom-Right corner of bullet
     float BLx = bulletPos.x - bulletOffset, BLy = bulletPos.y + bulletOffset;  //Bottom-Left corner of bullet
     float TLx = bulletPos.x - bulletOffset, TLy = bulletPos.y - bulletOffset;  //Top-Left corner of bullet
     //Bounds of enemy area to check for
     float leftBound  = enemyPos.x - enemyOffset;
     float rightBound = enemyPos.x + enemyOffset;
     float upperBound = enemyPos.y - enemyOffset;
     float lowerBound = enemyPos.y + enemyOffset;
     //Check if any corner of bullet is in enemy area bounds
     if(TRx >= leftBound && TRx <= rightBound && TRy >= upperBound && TRy <= lowerBound) return true;
     if(BRx >= leftBound && BRx <= rightBound && BRy >= upperBound && BRy <= lowerBound) return true;
     if(BLx >= leftBound && BLx <= rightBound && BLy >= upperBound && BLy <= lowerBound) return true;
     if(TLx >= leftBound && TLx <= rightBound && TLy >= upperBound && TLy <= lowerBound) return true;
     return false;
}
//Update sprite position using velocity vector
void Weapon::updatePos()
{
    bullet.move(velocity);
}
