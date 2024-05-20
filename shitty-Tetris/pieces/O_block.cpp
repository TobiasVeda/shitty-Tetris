//
// Created by tobia on 23.04.2024.
//

#include <SFML/Graphics.hpp>
#include "O_block.h"
#include "../Constants.h"

O_block::O_block(sf::Vector2f position){
    _type = Constants::Block_types::O;
    _placed = false;
    auto block_color = sf::Color::Yellow;
    auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);
    int x = (int)Constants::tilesize.x;
    int y = (int)Constants::tilesize.y;

    if (_texture.loadFromFile(Constants::texture_name, sf::IntRect(2*x, 0*y, x, y))){
        _r1.setTexture(&_texture);
        _r2.setTexture(&_texture);
        _r3.setTexture(&_texture);
        _r4.setTexture(&_texture);
    } else{
        _r1.setFillColor(block_color);
        _r2.setFillColor(block_color);
        _r3.setFillColor(block_color);
        _r4.setFillColor(block_color);
    }

    _r1.setOrigin(sf::Vector2f(40, 40));
    _r2.setOrigin(sf::Vector2f(0, 40));
    _r3.setOrigin(sf::Vector2f(40, 0));
    _r4.setOrigin(sf::Vector2f(0, 0));

    _r1.setPosition(position);
    _r2.setPosition(position);
    _r3.setPosition(position);
    _r4.setPosition(position);

    _r1.setSize(tilesize_f);
    _r2.setSize(tilesize_f);
    _r3.setSize(tilesize_f);
    _r4.setSize(tilesize_f);
}