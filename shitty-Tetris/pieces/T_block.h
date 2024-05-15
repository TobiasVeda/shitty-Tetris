//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_T_BLOCK_H
#define TILEMAP_T_BLOCK_H

#include <SFML/Graphics.hpp>
#include "Base_shape.h"

class T_block : public Base_shape{
public:
    T_block(sf::Vector2f position = sf::Vector2f(0, 0));
};


#endif //TILEMAP_T_BLOCK_H
