//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_BLOCK_BAG_H
#define TILEMAP_BLOCK_BAG_H

#include "pieces/Base_shape.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>

class Block_generator {
private:

    std::vector<Block_types> _bag;
    std::vector<Block_types> _next;

    Block_types get_rand_from_bag();
    Block_types get_next_blocktype();

public:
    Block_generator();

    Base_shape* generate(Block_types type = Block_types::Ndef);
    std::vector<Block_types>& get_next_vector();
};


#endif //TILEMAP_BLOCK_BAG_H
