#include "weapont3.h"

WeaponT3::WeaponT3()
{
    velocity.x = 0;
    velocity.y = 0;
}

WeaponT3::WeaponT3(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture)
{
    bullet.setTexture(texture);
    bullet.setOrigin(bulletOffset, bulletOffset);
    bullet.setPosition(position);
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 1)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi + .06f;
        x = -cosf(theta);
        y = sinf(theta);
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 2)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi + .03f;
        x = -cosf(theta);
        y = sinf(theta);
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
    //Sets bullet velocity vector to acceptable aimVector value
    if(bulletNumber == 3)
    {
        float invMagnitude = (1/sqrtf(aimVector.x*aimVector.x + aimVector.y*aimVector.y));
        velocity.x = aimVector.x*invMagnitude*bulletVelocity;
        velocity.y = aimVector.y*invMagnitude*bulletVelocity;
        float angle = atan2f(velocity.x,velocity.y) * -RadtoDeg;
        bullet.setRotation(angle);
    }
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 4)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi - .03f;
        x = -cosf(theta);
        y = sinf(theta);
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
    //Deviates bullet velocity from aimVector slightly
    if(bulletNumber == 5)
    {
        float x,y,invMagnitude, phi, theta;
        phi = atan2f(aimVector.x,aimVector.y);
        theta = phi - .06f;
        x = -cosf(theta);
        y = sinf(theta);
        invMagnitude = 1/sqrtf(x*x + y*y);
        velocity.x = y*invMagnitude*bulletVelocity;
        velocity.y = -x*invMagnitude*bulletVelocity;
        bullet.setRotation(theta);
    }
}
