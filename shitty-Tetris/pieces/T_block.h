//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_T_BLOCK_H
#define TILEMAP_T_BLOCK_H

#include <SFML/Graphics.hpp>
#include "Base_shape.h"
#include "../Game.h"

class T_block : public Base_shape{
public:
    explicit T_block(Game*);
};


#endif //TILEMAP_T_BLOCK_H
