//
// Created by tobia on 23.04.2024.
//

#ifndef TILEMAP_PIECE_COLLECTION_H
#define TILEMAP_PIECE_COLLECTION_H

#include <SFML/Graphics.hpp>
#include <list>
#include "pieces/Base_shape.h"


class Block_stack{
protected:
    static inline std::list<Base_shape> _block_stack;

public:
    static void add_to_collection(Base_shape*);
    static const std::list<Base_shape>* get_stack();

};


#endif //TILEMAP_PIECE_COLLECTION_H
