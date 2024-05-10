//
// Created by tobia on 23.04.2024.
//

#include "O_block.h"
#include "../Game.h"

O_block::O_block(Game *game){
    _game = game;
    _placed = false;
    auto block_color = sf::Color::Yellow;
    auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);

    _r1.setOrigin(sf::Vector2f(40, 40));
    _r2.setOrigin(sf::Vector2f(0, 40));
    _r3.setOrigin(sf::Vector2f(40, 0));
    _r4.setOrigin(sf::Vector2f(0, 0));

    _r1.setPosition(sf::Vector2f(200, 40));
    _r2.setPosition(sf::Vector2f(200, 40));
    _r3.setPosition(sf::Vector2f(200, 40));
    _r4.setPosition(sf::Vector2f(200, 40));

    _tetris_piece.push_back(_r1);
    _tetris_piece.push_back(_r2);
    _tetris_piece.push_back(_r3);
    _tetris_piece.push_back(_r4);

    for (auto& i : _tetris_piece) {
        // setSize need float, but Constants::tilesize is uint
        i.setSize(tilesize_f);
        i.setFillColor(block_color);
    }

}