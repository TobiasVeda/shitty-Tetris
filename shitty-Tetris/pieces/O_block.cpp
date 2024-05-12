//
// Created by tobia on 23.04.2024.
//

#include <SFML/Graphics.hpp>
#include "O_block.h"


O_block::O_block(){

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

    _r1.setSize(tilesize_f);
    _r2.setSize(tilesize_f);
    _r3.setSize(tilesize_f);
    _r4.setSize(tilesize_f);

    _r1.setFillColor(block_color);
    _r2.setFillColor(block_color);
    _r3.setFillColor(block_color);
    _r4.setFillColor(block_color);
}