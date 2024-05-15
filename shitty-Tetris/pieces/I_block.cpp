//
// Created by tobia on 28.04.2024.
//

#include <SFML/Graphics.hpp>
#include "I_block.h"
#include "../Constants.h"

I_block::I_block(sf::Vector2f position){
    _type = Constants::Block_types::I;
    _placed = false;
    auto block_color = sf::Color::Cyan;
    auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);
    // setSize need float, but Constants::tilesize is uint

    _r1.setOrigin(sf::Vector2f(80, 40));
    _r2.setOrigin(sf::Vector2f(40, 40));
    _r3.setOrigin(sf::Vector2f(0, 40));
    _r4.setOrigin(sf::Vector2f(-40, 40));

    _r1.setPosition(position);
    _r2.setPosition(position);
    _r3.setPosition(position);
    _r4.setPosition(position);

    _r1.setSize(tilesize_f);
    _r2.setSize(tilesize_f);
    _r3.setSize(tilesize_f);
    _r4.setSize(tilesize_f);

    _r1.setFillColor(block_color);
    _r2.setFillColor(block_color);
    _r3.setFillColor(block_color);
    _r4.setFillColor(block_color);
}