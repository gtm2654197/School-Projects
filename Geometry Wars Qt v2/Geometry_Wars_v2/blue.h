#ifndef BLUE_H
#define BLUE_H

#include "enemy.h"

class Blue : public Enemy
{
public:
    Blue();                                              //Default Constructor
    Blue(sf::Vector2f position, sf::Texture& texture);   //Constructor takes in position and texture
    ~Blue();                                             //Destructor
};

#endif // BLUE_H
