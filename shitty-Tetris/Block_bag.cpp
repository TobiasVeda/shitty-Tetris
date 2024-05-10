//
// Created by tobia on 23.04.2024.
//

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "pieces/all_pieces.h"
#include "Block_bag.h"
#include <random>
#include <string>
#include <iostream>
#include "Game.h"

void Block_bag::get_new_block(Base_shape *block, Game *game) {

    if (_bag.empty()) {
        _bag.emplace_back("T");
        _bag.emplace_back("O");
        _bag.emplace_back("L");
        _bag.emplace_back("I");
        _bag.emplace_back("J");
        _bag.emplace_back("Z");
        _bag.emplace_back("S");
    }

        std::mt19937 rng(rand() * time(NULL));
        std::uniform_int_distribution<int> gen(0, _bag.size()-1);
        int i = gen(rng);

    if (_bag[i] == "T"){
        _bag.erase(_bag.begin() + i);
        T_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "O"){
        _bag.erase(_bag.begin() + i);
        O_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "L"){
        _bag.erase(_bag.begin() + i);
        L_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "I"){
        _bag.erase(_bag.begin() + i);
        I_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "J"){
        _bag.erase(_bag.begin() + i);
        J_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "Z"){
        _bag.erase(_bag.begin() + i);
        Z_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    } else if (_bag[i] == "S"){
        _bag.erase(_bag.begin() + i);
        S_block new_player_controlled_block(game);
        *block = new_player_controlled_block;
    }
}