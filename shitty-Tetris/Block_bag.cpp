//
// Created by tobia on 23.04.2024.
//
#include "Block_bag.h"
#include "model/pieces/Base_shape.h"
#include "model/pieces/all_pieces.h"
#include <SFML/Graphics.hpp>
#include <random>

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

Base_shape* Block_bag::get_new_block(Constants::Block_types type) {
    // If an error occurs in determining block to be returned, function will
    // return an L. Will also happen if trying to get block og type Ndef


    switch (type) {
        case Constants::T:
            return new T_block(sf::Vector2f(180, 20));
        case Constants::O:
            return new O_block(sf::Vector2f(200, 40));
        case Constants::L:
            return new L_block(sf::Vector2f(180, 60));
        case Constants::I:
            return new I_block(sf::Vector2f(200, 40));
        case Constants::J:
            return new J_block(sf::Vector2f(180, 60));
        case Constants::Z:
            return new Z_block(sf::Vector2f(180, 20));
        case Constants::S:
            return new S_block(sf::Vector2f(180, 20));
        default:
            return new L_block(sf::Vector2f(180, 60));
    }
}

std::vector<Constants::Block_types>& Block_bag::get_next_vector() {
    return _next;
}