#ifndef PURPLE_H
#define PURPLE_H

#include <cstdlib>
#include <time.h>
#include "enemy.h"

class Purple: public Enemy
{
public:
    Purple();
    Purple(sf::Vector2f position, sf::Texture& texture);
    ~Purple();

    void randomVector();  //Assigns random velocity vector on spawn
};

#endif // PURPLE_H
