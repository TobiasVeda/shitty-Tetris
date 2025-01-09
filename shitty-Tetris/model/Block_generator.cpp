//
// Created by tobia on 23.04.2024.
//
#include "Block_generator.h"
#include "pieces/Base_shape.h"
#include "pieces/all_pieces.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <random>

Block_generator::Block_generator() {

    if (_bag.empty()) {
        _bag.emplace_back(Block_types::T);
        _bag.emplace_back(Block_types::O);
        _bag.emplace_back(Block_types::L);
        _bag.emplace_back(Block_types::I);
        _bag.emplace_back(Block_types::J);
        _bag.emplace_back(Block_types::Z);
        _bag.emplace_back(Block_types::S);
    }
    get_next_blocktype();
}

Block_types Block_generator::get_rand_from_bag(){
    // Start with a full bag, and randomly removes one block for each call.
    // When bag is empty, it is refilled, and blocks are again randomly removed.

    std::mt19937 rng(rand() * time(NULL));
    std::uniform_int_distribution<int> gen(0, _bag.size()-1);
    int i = gen(rng);

    Block_types return_value = _bag[i];
    _bag.erase(_bag.begin() + i);


    if (_bag.size() == 0) {
        _bag.emplace_back(Block_types::T);
        _bag.emplace_back(Block_types::O);
        _bag.emplace_back(Block_types::L);
        _bag.emplace_back(Block_types::I);
        _bag.emplace_back(Block_types::J);
        _bag.emplace_back(Block_types::Z);
        _bag.emplace_back(Block_types::S);
    }


    return return_value;
}

Block_types Block_generator::get_next_blocktype() {

    while(_next.size() <= 3){

        _next.emplace_back(get_rand_from_bag());
    }

    Block_types return_value = _next[0];
    _next.erase(_next.begin());
    return return_value;
}

Base_shape* Block_generator::generate(Block_types type) {
    // If an error occurs in determining block to be returned, function will
    // take the L.

    if (type == Block_types::Ndef){
        type = get_next_blocktype();
    }

    switch (type) {
        case Block_types::T:
            return new T_block(sf::Vector2f(180, -20));
        case Block_types::O:
            return new O_block(sf::Vector2f(200, 0));
        case Block_types::L:
            return new L_block(sf::Vector2f(180, 20));
        case Block_types::I:
            return new I_block(sf::Vector2f(200, 0));
        case Block_types::J:
            return new J_block(sf::Vector2f(180, 20));
        case Block_types::Z:
            return new Z_block(sf::Vector2f(180, -20));
        case Block_types::S:
            return new S_block(sf::Vector2f(180, -20));
        default:
            return new L_block(sf::Vector2f(180, 20));
    }
}

std::vector<Block_types>& Block_generator::get_next_vector() {
    return _next;
}