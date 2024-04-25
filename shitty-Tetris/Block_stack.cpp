//
// Created by tobia on 23.04.2024.
//

#include "Block_stack.h"


void Block_stack::add_to_collection(Base_shape *block) {
    _block_stack.emplace_back(*block);
}

const std::list<Base_shape>* Block_stack::get_stack(){
    return &_block_stack;
}
