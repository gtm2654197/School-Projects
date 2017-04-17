#ifndef WEAPONT1_H
#define WEAPONT1_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "weapon.h"

class WeaponT1 : public Weapon
{
public:
    WeaponT1();
    WeaponT1(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture);
};

#endif // WEAPONT1_H
