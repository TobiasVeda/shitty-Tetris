//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_O_BLOCK_H
#define TILEMAP_O_BLOCK_H

#include "Base_shape.h"
#include <SFML/Graphics.hpp>

class O_block : public Base_shape{
public:
    O_block(sf::Vector2f position = sf::Vector2f(0, 0));
};


#endif //TILEMAP_O_BLOCK_H
