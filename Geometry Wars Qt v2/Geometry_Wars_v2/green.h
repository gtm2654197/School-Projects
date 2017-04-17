#ifndef GREEN_H
#define GREEN_H

#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "weapon.h"

class Green : public Enemy
{
public:
    Green();
    Green(sf::Vector2f position, sf::Texture& texture);
    ~Green();
};

#endif // GREEN_H
