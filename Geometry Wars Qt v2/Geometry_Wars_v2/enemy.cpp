#include "enemy.h"

//Default Constructor
Enemy::Enemy()
{
    enemyType = "";
    accel = sf::Vector2f(0.f,0.f);
    accelbyBullet = sf::Vector2f(0.f,0.f);
    velocity = sf::Vector2f(0.f,0.f);
    angle = 0;    
    direction = true;
    dodging = false;
}
//Place holder for child class constructors
Enemy::Enemy(sf::Vector2f position, sf::Texture& texture)
{

}
Enemy::~Enemy()
{

}
//Returns sprite for window to draw in game class
sf::Sprite &Enemy::Draw()
{
    return sprite;
}
//Checks for enemy type and updates movement based on that
void Enemy::updatePos(sf::Vector2f playerPos)
{
    if(enemyType == "Blue")
    {
        //Calls follow player to add acceleration toward player
        followPlayer(playerPos, maxBlueVel, blueAccel);
        //Moves sprite using velocity vector
        sprite.move(velocity);
        //Rotates sprite back and forth
        if(direction == true)
        {
            angle++;
            sprite.setRotation(angle);
            if(angle > 30) direction = false;
        }
        if(direction == false)
        {
            angle--;
            sprite.setRotation(angle);
            if(angle < -30) direction = true;
        }
    }
    //Called for green type only when no bullets exist
    if(enemyType == "Green")
    {
        //Calls follow player to add acceleration toward player
        followPlayer(playerPos, maxGreenVel, greenAccel);
        //Moves sprite using velocity vector
        sprite.move(velocity);
        //Rotates sprite
        if(direction == true)
        {
            angle-=2;
            sprite.setRotation(angle);
            if(angle < -225) direction = false;
        }
        if(direction == false)
        {
            angle+=2;
            sprite.setRotation(angle);
            if(angle > 225) direction = true;
        }
    }
    //Purple enemy rotates clockwise and does not follow player
    if(enemyType == "Purple")
    {        
        sprite.move(velocity);
        angle+=4;
        if(angle >= 360) angle = 0;
        sprite.setRotation(angle);
        //Resolves unique purple border collision to "bounce" off border
        borderCollisionPurple();
    }
    //Pink has same movement mechanics as blue, but faster maxVelocity
    //and faster acceleration, as well as having different rotation
    if(enemyType == "Pink")
    {
        followPlayer(playerPos, maxPinkVel, pinkAccel);
        sprite.move(velocity);
        if(direction == false)
        {
            angle-=2;
            sprite.setRotation(angle);
            if(angle < -225) direction = false;
        }
        if(direction == true)
        {
            angle+=2;
            sprite.setRotation(angle);
            if(angle > 225) direction = true;
        }
    }
    //Same mechanics as pink enemy, but a bit slower
    if(enemyType == "smallPink")
    {
        followPlayer(playerPos, maxsmallPinkVel, smallpinkAccel);
        sprite.move(velocity);
        if(direction == false)
        {
            angle-=2;
            sprite.setRotation(angle);
            if(angle < -225) direction = false;
        }
        if(direction == true)
        {
            angle+=2;
            sprite.setRotation(angle);
            if(angle > 225) direction = true;
        }
    }
    //Resolves border collision for all enemy types
    borderCollision();
}
//Setter function for sprite position
void Enemy::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
}
//Checks for border collision with sprite and resolves
void Enemy::borderCollisionPurple()
{
    sf::Vector2f pos = sprite.getPosition();                               //Sprite position
    if((pos.x < enemyOffset          && pos.y <  enemyOffset)          ||  //If in top left corner
       (pos.x < enemyOffset          && pos.y > (BORDER-enemyOffset))  ||  //or in bottom left corner
       (pos.x > (BORDER-enemyOffset) && pos.y <  enemyOffset)          ||  //or in top right corner
       (pos.x > (BORDER-enemyOffset) && pos.y > (BORDER-enemyOffset)))     //or in bottom right corner
    {
        velocity.x = -velocity.x;                                          //then reverse both x and y direction
        velocity.y = -velocity.y;
    }
    else if(pos.x < enemyOffset || pos.x > (BORDER-enemyOffset))           //If x is outside game borders
    {
        velocity.x = -velocity.x;                                          //reverse x direction
    }
    else if(pos.y < enemyOffset || pos.y > (BORDER-enemyOffset))           //If y is outside game borders
    {
        velocity.y = -velocity.y;                                          //Reverse y direction
    }
}
//If enemy exceeds border boundaries, moves enemy back in bounds
void Enemy::borderCollision()
{
    sf::Vector2f pos = sprite.getPosition();
    if(pos.x < enemyOffset && pos.y < enemyOffset)
    {
        pos.x = enemyOffset;
        pos.y = enemyOffset;
    }
    else if(pos.x < enemyOffset && pos.y > (BORDER-enemyOffset))
    {
        pos.x = enemyOffset;
        pos.y = BORDER - enemyOffset;
    }
    else if(pos.x > (BORDER-enemyOffset) && pos.y < enemyOffset)
    {
        pos.x = BORDER-enemyOffset;
        pos.y = enemyOffset;
    }
    else if(pos.x > (BORDER-enemyOffset) && pos.y > (BORDER-enemyOffset))
    {
        pos.x = BORDER-enemyOffset;
        pos.y = BORDER - enemyOffset;
    }
    else if(pos.x < enemyOffset) pos.x = enemyOffset;
    else if (pos.x > (BORDER - enemyOffset)) pos.x = BORDER - enemyOffset;
    else if(pos.y < enemyOffset) pos.y = enemyOffset;
    else if(pos.y > (BORDER - enemyOffset)) pos.y = BORDER - enemyOffset;
    sprite.setPosition(pos.x, pos.y);
}
//Returns sprite position
sf::Vector2f Enemy::getPos()
{
    return sprite.getPosition();
}
//Returns enemy type as string
string Enemy::getType()
{
    return enemyType;
}
//Adds acceleration toward player, each enemy type has unique acceleration values
//and max speed, so some seem "heavier" than each other. This function gives the
//effect of inertia with changing acceleration vectors
void Enemy::followPlayer(sf::Vector2f playerPos, float maxVel, float acceleration)
{
    sf::Vector2f enemyPos = sprite.getPosition();
    float x = playerPos.x - enemyPos.x;  //i direction
    float y = playerPos.y - enemyPos.y;  //j direction
    float unitize = 1/sqrtf(x*x + y*y);  //form unit vector
    //unit vector times constant acceleration = acceleration vector pointing to player
    accel = sf::Vector2f(acceleration*x*unitize, acceleration*y*unitize);
    //Calculate current speed to see if max velocity already reached
    float speed = sqrtf(velocity.x*velocity.x + velocity.y*velocity.y);
    //if speed is over max velocity, add accleration to velocity
    //then unitize, and multiply by max velocity if speed still
    //exceeds max Velocity, else keep new velocity vector
    if(speed >= maxVel)
    {
        float oldVelX = velocity.x;
        float oldVelY = velocity.y;
        oldVelX += accel.x;
        oldVelY += accel.y;
        speed = sqrtf(oldVelX*oldVelX + oldVelY*oldVelY);
        if(speed >= maxVel)
        {
            velocity.x = oldVelX*(1/speed)*maxVel;
            velocity.y = oldVelY*(1/speed)*maxVel;
        }
        else
        {
            velocity.x = oldVelX;
            velocity.y = oldVelY;
        }
    }
    //if not max velocity, add acceleration vector
    else
    {
        velocity = sf::Vector2f(velocity.x += accel.x, velocity.y += accel.y);
    }
}
//Adds unique dodging feature of green enemy
//follows player if no bullet is in radius
void Enemy::greenUpdate(sf::Vector2f bulletPos)
{
    if(dodging == false)
    {
        sf::Vector2f enemyPos = sprite.getPosition();
        float x,y;
        float enemyAngle = atan2f(enemyPos.y,enemyPos.x);
        float bulletAngle = atan2f(bulletPos.y,bulletPos.x);
        //Find out which perpindicular vector to bullet vector
        //to use by comparing angles of bullet and enemy
        if(enemyAngle > bulletAngle)
        {
            x = -bulletPos.x;
            y = bulletPos.y;
        }
        else
        {
            x = bulletPos.x;
            y = -bulletPos.y;
        }
        //unitize and add accel to velocity
        //set dodging to true to prevent further
        //dodging until movement is complete
        float unitize = 1/sqrtf(x*x + y*y);
        accelbyBullet.x = x*unitize*dodgeAccel;
        accelbyBullet.y = y*unitize*dodgeAccel;
        velocity.x = accelbyBullet.x;
        velocity.y = accelbyBullet.y;
        dodging = true;

    }
    //Continues decrementing acceleration of dodge until it
    //is less than threshhold then sets dodging to false again
    else
    {
        if(fabs(accelbyBullet.x) <= .1 && fabs(accelbyBullet.y) <= .1)
        {
            accelbyBullet.x = 0.f;
            accelbyBullet.y = 0.f;
            dodging = false;
        }
        else
        {
            accelbyBullet.x *= .9f;
            accelbyBullet.y *= .9f;
        }
        velocity.x = accelbyBullet.x;
        velocity.y = accelbyBullet.y;
    }
    sprite.move(velocity);
    if(direction == true)
    {
        angle-=2;
        sprite.setRotation(angle);
        if(angle < -225) direction = false;
    }
    if(direction == false)
    {
        angle+=2;
        sprite.setRotation(angle);
        if(angle > 225) direction = true;
    }
    //Checks for border collision and resolves
    borderCollision();
}
//Returns true for bullet in radius of green enemy
bool Enemy::bulletinRadius(sf::Vector2f bulletPos)
{
    sf::Vector2f enemyPos = sprite.getPosition();
    float deltaX = bulletPos.x - enemyPos.x;
    float deltaY = bulletPos.y - enemyPos.y;
    float radius = sqrtf(deltaX*deltaX + deltaY*deltaY);
    if(radius < greenBulletRadius) return true;
    return false;
}
//Resolves some enemy collision with each other
//to avoid bunching, overlapping is allowed,
//but enemies prefer to keep apart
void Enemy::enemyCollision(sf::Vector2f enemyPos)
{
    sf::Vector2f myPos = sprite.getPosition();
    float deltaX, deltaY;
    deltaX = myPos.x - enemyPos.x;
    deltaY = myPos.y - enemyPos.y;
    float distance = sqrt(deltaX*deltaX + deltaY*deltaY);
    if(distance < enemyOffset)
    {
        velocity.x *= .75f;
        velocity.y *= .75f;
    }
}
//Returns color of enemy type
sf::Color Enemy::getColor()
{
    if(enemyType == "Blue") return sf::Color(0,255,186,255);
    if(enemyType == "Purple") return sf::Color(255,0,174,255);
    if(enemyType == "Green") return sf::Color(0,255,78,255);
    if(enemyType == "Pink" || enemyType == "smallPink") return sf::Color(255,135,228,255);
}

