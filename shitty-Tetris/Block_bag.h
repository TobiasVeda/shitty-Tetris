//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_BLOCK_BAG_H
#define TILEMAP_BLOCK_BAG_H

#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "pieces/Base_shape.h"
#include <vector>

class Block_bag {
protected:
    static inline std::vector<Constants::Block_types> _bag;
        // Linking error if not inline
    static int get_new_blocktype_index();
public:
    static Base_shape get_new_block(); // need pointer to main object
};


#endif //TILEMAP_BLOCK_BAG_H
