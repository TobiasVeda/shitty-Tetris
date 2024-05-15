//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_L_BLOCK_H
#define SHITTY_TETRIS_L_BLOCK_H

#include <SFML/Graphics.hpp>
#include "Base_shape.h"

class L_block : public Base_shape{
public:
    L_block(sf::Vector2f position = sf::Vector2f(0, 0));
};


#endif //SHITTY_TETRIS_L_BLOCK_H
