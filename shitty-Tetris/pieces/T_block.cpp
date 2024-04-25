//
// Created by tobia on 20.04.2024.
//

#include "T_block.h"
T_block::T_block(){
    _placed = false;
    auto block_color = sf::Color::Magenta;
    auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);

    _r1.setPosition(sf::Vector2f(0,0));
    _r2.setPosition(sf::Vector2f(40,0));
    _r3.setPosition(sf::Vector2f(80,0));
    _r4.setPosition(sf::Vector2f(40,40));
//        can be made relative probably

    _tetris_piece.push_back(_r1);
    _tetris_piece.push_back(_r2);
    _tetris_piece.push_back(_r3);
    _tetris_piece.push_back(_r4);

    for (auto& i : _tetris_piece) {
        // setSize need float, but Constants::tilesize is uint
        i.setSize(tilesize_f);
    }

    for (auto& i : _tetris_piece) {
        // setSize need float, but Constants::tilesize is uint
        i.setFillColor(block_color);
    }

//        auto half_diagonal = sf::Vector2f((float)80/2, (float)80/2);
    _rotation_center = sf::Vector2f(120,40);
//                r2.getPosition() + half_diagonal;
}