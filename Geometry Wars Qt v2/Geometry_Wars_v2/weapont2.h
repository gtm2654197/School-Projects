#ifndef WEAPONT2_H
#define WEAPONT2_H

#include "weapon.h"

class WeaponT2 : public Weapon
{
public:
    WeaponT2();
    WeaponT2(int bulletNumber, const sf::Vector2f& position, const sf::Vector2f& aimVector, const sf::Texture& texture);
};

#endif // WEAPONT2_H
