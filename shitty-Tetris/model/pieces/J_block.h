//
// Created by tobia on 28.04.2024.
//

#ifndef SHITTY_TETRIS_J_BLOCK_H
#define SHITTY_TETRIS_J_BLOCK_H

#include "Base_shape.h"
#include <SFML/Graphics.hpp>

class J_block : public Base_shape{
public:
    J_block(sf::Vector2f position = sf::Vector2f(0, 0));
};


#endif //SHITTY_TETRIS_J_BLOCK_H
