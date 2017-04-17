#include "weapont1.h"

WeaponT1::WeaponT1()
{
    velocity.x = 0;
    velocity.y = 0;
}

WeaponT1::WeaponT1(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture)
{
    if(bulletNumber == 1)
    {
        bullet.setTexture(texture);
        bullet.setOrigin(bulletOffset, bulletOffset);                                      //set sprite origin to center
        bullet.setPosition(position);                                                      //spawn bullet at player position        
        float invMagnitude = (1/sqrtf(aimVector.x*aimVector.x + aimVector.y*aimVector.y)); //for unitizing vector
        velocity.x = aimVector.x*invMagnitude*bulletVelocity;                              //unit vector * max velocity scalar
        velocity.y = aimVector.y*invMagnitude*bulletVelocity;                              //unit vector * max velocity scalar
        float angle = atanf(velocity.x/velocity.y) * -RadtoDeg;                            //get angle for velocity vector from y-axis;
        bullet.setRotation(angle);
    }
}
