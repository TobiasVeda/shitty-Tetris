//
// Created by tobia on 28.04.2024.
//

#include "J_block.h"


J_block::J_block(){
    _placed = false;
    auto block_color = sf::Color(251, 148, 3);
    auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);

    _r1.setOrigin(sf::Vector2f(60, 60));
    _r2.setOrigin(sf::Vector2f(60, 20));
    _r3.setOrigin(sf::Vector2f(20, 20));
    _r4.setOrigin(sf::Vector2f(-20, 20));

    _r1.setPosition(sf::Vector2f(180, 60));
    _r2.setPosition(sf::Vector2f(180, 60));
    _r3.setPosition(sf::Vector2f(180, 60));
    _r4.setPosition(sf::Vector2f(180, 60));

    _r1.setSize(tilesize_f);
    _r2.setSize(tilesize_f);
    _r3.setSize(tilesize_f);
    _r4.setSize(tilesize_f);

    _r1.setFillColor(block_color);
    _r2.setFillColor(block_color);
    _r3.setFillColor(block_color);
    _r4.setFillColor(block_color);
}