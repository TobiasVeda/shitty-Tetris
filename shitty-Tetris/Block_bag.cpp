//
// Created by tobia on 23.04.2024.
//
#include "Block_bag.h"
#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "pieces/all_pieces.h"
#include <random>
#include "Game.h"

Constants::Block_types Block_bag::get_block_from_bag(){
    // Start with a full bag, and randomly removes one block for each call.
    // When bag is empty, it is refilled, and blocks are again randomly removed.

    if (_bag.empty()) {
        _bag.emplace_back(Constants::T);
        _bag.emplace_back(Constants::O);
        _bag.emplace_back(Constants::L);
        _bag.emplace_back(Constants::I);
        _bag.emplace_back(Constants::J);
        _bag.emplace_back(Constants::Z);
        _bag.emplace_back(Constants::S);
    }

    std::mt19937 rng(rand() * time(NULL));
    std::uniform_int_distribution<int> gen(0, _bag.size()-1);
    int i = gen(rng);

    Constants::Block_types return_value = _bag[i];
    _bag.erase(_bag.begin() + i);
    return return_value;
}

Constants::Block_types Block_bag::get_new_blocktype_index() {

    int number_of_next = 5;
    while(_next.size() < number_of_next){

        _next.emplace_back(get_block_from_bag());
    }

    Constants::Block_types return_value = _next[0];
    _next.erase(_next.begin());
    return return_value;
}

Base_shape Block_bag::get_new_block(Constants::Block_types type) {

    switch (type) {
        case Constants::T:
            return T_block();
        case Constants::O:
            return O_block();
        case Constants::L:
            return L_block();
        case Constants::I:
            return I_block();
        case Constants::J:
            return J_block();
        case Constants::Z:
            return Z_block();
        case Constants::S:
            return S_block();
        default:
            return L_block();
    }

}

std::vector<Constants::Block_types>& Block_bag::get_next_vector() {
    return _next;
}