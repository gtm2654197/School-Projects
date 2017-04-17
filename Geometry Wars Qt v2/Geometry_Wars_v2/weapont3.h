#ifndef WEAPONT3_H
#define WEAPONT3_H

#include "weapon.h"

class WeaponT3 : public Weapon
{
public:
    WeaponT3();
    WeaponT3(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture);
};

#endif // WEAPONT3_H
