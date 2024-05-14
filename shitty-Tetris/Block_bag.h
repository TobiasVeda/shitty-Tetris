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
    static inline std::vector<Constants::Block_types> _next;

    static Constants::Block_types get_block_from_bag();
    static Constants::Block_types get_new_blocktype_index();
public:
    static Base_shape get_new_block(Constants::Block_types type = get_new_blocktype_index());
    static std::vector<Constants::Block_types>& get_next_vector();
};


#endif //TILEMAP_BLOCK_BAG_H
