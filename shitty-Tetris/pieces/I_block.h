//
// Created by tobia on 28.04.2024.
//

#ifndef SHITTY_TETRIS_I_BLOCK_H
#define SHITTY_TETRIS_I_BLOCK_H

#include <SFML/Graphics.hpp>
#include "Base_shape.h"

class I_block : public Base_shape{
public:
    I_block(sf::Vector2f position = sf::Vector2f(0, 0));
};


#endif //SHITTY_TETRIS_I_BLOCK_H
