//
// Created by tobia on 23.04.2024.
//

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "pieces/T_block.h"
#include "pieces/O_block.h"
#include "Block_bag.h"
#include <random>
#include <string>
#include <iostream>

Base_shape Block_bag::get_new_block() {

    if (_bag.empty()) {
        _bag.emplace_back("T");
        _bag.emplace_back("O");
    }

        std::mt19937 rng(rand() * time(NULL));
        std::uniform_int_distribution<int> gen(0, _bag.size()-1);
        int i = gen(rng);

    if (_bag[i] == "T"){
        _bag.erase(_bag.begin() + i);
        static T_block new_player_controlled_block;
        // cant create new with static
        return new_player_controlled_block;
    }
    if (_bag[i] == "O"){
        _bag.erase(_bag.begin() + i);
        static O_block new_player_controlled_block;
        return new_player_controlled_block;
    }

    static O_block oops_something_went_wrong_here_is_an_O_block;
    return oops_something_went_wrong_here_is_an_O_block;
}