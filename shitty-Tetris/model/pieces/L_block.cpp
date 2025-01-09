//
// Created by tobia on 26.04.2024.
//

#include "L_block.h"
#include "../../Enumerations.h"
#include "../../Constants.h"
#include <SFML/Graphics.hpp>

L_block::L_block(sf::Vector2f position){
    _type = Block_types::L;
    _placed = false;
    auto block_color = sf::Color(251, 148, 3); // Orange
    sf::Vector2f tilesize_f((float)Constants::tilesize.x - 0.5f, (float)Constants::tilesize.y - 0.5f);
    int x = (int)Constants::tilesize.x;
    int y = (int)Constants::tilesize.y;

    if (_texture.loadFromImage(_tileset, sf::IntRect(2*x, y, x, y))){
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

    _r1.setOrigin(sf::Vector2f(60, 20));
    _r2.setOrigin(sf::Vector2f(20, 20));
    _r3.setOrigin(sf::Vector2f(-20, 20));
    _r4.setOrigin(sf::Vector2f(-20, 60));

    _r1.setPosition(position);
    _r2.setPosition(position);
    _r3.setPosition(position);
    _r4.setPosition(position);

    _r1.setSize(tilesize_f);
    _r2.setSize(tilesize_f);
    _r3.setSize(tilesize_f);
    _r4.setSize(tilesize_f);
}
