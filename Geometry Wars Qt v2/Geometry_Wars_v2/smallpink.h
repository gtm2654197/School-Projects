#ifndef SMALLPINK_H
#define SMALLPINK_H

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <time.h>
#include "enemy.h"


class smallPink : public Enemy
{
public:
    smallPink();
    smallPink(sf::Vector2f position, sf::Texture& texture);
    ~smallPink();

    //Assigns random velocity vector on spawn
    void randVelocity();
    //Assigns random position within position radius on spawn
    void Spawn(sf::Vector2f position);
};

#endif // SMALLPINK_H
