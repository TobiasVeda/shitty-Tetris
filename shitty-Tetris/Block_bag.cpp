//
// Created by tobia on 23.04.2024.
//
#include "Block_bag.h"
#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "pieces/all_pieces.h"
#include <random>
#include "Game.h"

enum{T=0, O=1, L=2, I=3, J=4, Z=5, S=6};

int Block_bag::get_new_blocktype_index() {
    if (_bag.empty()) {
        _bag.emplace_back(T);
        _bag.emplace_back(O);
        _bag.emplace_back(L);
        _bag.emplace_back(I);
        _bag.emplace_back(J);
        _bag.emplace_back(Z);
        _bag.emplace_back(S);
    }

    std::mt19937 rng(rand() * time(NULL));
    std::uniform_int_distribution<int> gen(0, _bag.size()-1);
    int i = gen(rng);

    return i;
}

Base_shape Block_bag::get_new_block() {

    int i = get_new_blocktype_index();

    switch (_bag[i]) {
        case T:
            _bag.erase(_bag.begin() + i);
            return T_block();
        case O:
            _bag.erase(_bag.begin() + i);
            return O_block();
        case L:
            _bag.erase(_bag.begin() + i);
            return L_block();
        case I:
            _bag.erase(_bag.begin() + i);
            return I_block();
        case J:
            _bag.erase(_bag.begin() + i);
            return J_block();
        case Z:
            _bag.erase(_bag.begin() + i);
            return Z_block();
        case S:
            _bag.erase(_bag.begin() + i);
            return S_block();
        default:
            return L_block();
    }

}