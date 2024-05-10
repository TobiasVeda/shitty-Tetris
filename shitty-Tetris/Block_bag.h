//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_BLOCK_BAG_H
#define TILEMAP_BLOCK_BAG_H

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include <string>
#include <vector>
#include "Game.h"

class Block_bag {
protected:
    static inline std::vector<std::string> _bag;
        // Linking error if not inline

public:
    static void get_new_block(Base_shape*, Game*); // need pointer to main object
};


#endif //TILEMAP_BLOCK_BAG_H
