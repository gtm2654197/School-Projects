#ifndef PINK_H
#define PINK_H

#include <SFML/Graphics.hpp>
#include "enemy.h"

class Pink : public Enemy
{
public:
    Pink();
    Pink(sf::Vector2f position, sf::Texture& texture);
    ~Pink();
};

#endif // PINK_H
