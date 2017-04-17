#include "weapont2.h"

WeaponT2::WeaponT2()
{
    velocity.x = 0;
    velocity.y = 0;
}

WeaponT2::WeaponT2(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture)
{
    bullet.setTexture(texture);
    bullet.setOrigin(bulletOffset, bulletOffset);   //set sprite origin to center
    bullet.setPosition(position);
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 1)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi + .085f;
        x = -cosf(theta);
        y = sinf(theta);
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
    //Sets bullet velocity vector to acceptable aimVector value
    if(bulletNumber == 2)
    {
        float invMagnitude = (1/sqrtf(aimVector.x*aimVector.x + aimVector.y*aimVector.y));
        velocity.x = aimVector.x*invMagnitude*bulletVelocity;
        velocity.y = aimVector.y*invMagnitude*bulletVelocity;
        float angle = atan2f(velocity.x,velocity.y) * -RadtoDeg;
        bullet.setRotation(angle);
    }
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 3)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi+ - .085f;
        x = -cosf(theta);
        y = sinf(theta);        
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
}
