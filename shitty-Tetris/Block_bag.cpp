//
// Created by tobia on 23.04.2024.
//
#include "Block_bag.h"
#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "pieces/all_pieces.h"
#include <random>
#include "Game.h"



int Block_bag::get_new_blocktype_index() {
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

    return i;
}

Base_shape Block_bag::get_new_block() {

    int i = get_new_blocktype_index();

    switch (_bag[i]) {
        case Constants::T:
            _bag.erase(_bag.begin() + i);
            return T_block();
        case Constants::O:
            _bag.erase(_bag.begin() + i);
            return O_block();
        case Constants::L:
            _bag.erase(_bag.begin() + i);
            return L_block();
        case Constants::I:
            _bag.erase(_bag.begin() + i);
            return I_block();
        case Constants::J:
            _bag.erase(_bag.begin() + i);
            return J_block();
        case Constants::Z:
            _bag.erase(_bag.begin() + i);
            return Z_block();
        case Constants::S:
            _bag.erase(_bag.begin() + i);
            return S_block();
        default:
            return L_block();
    }

}