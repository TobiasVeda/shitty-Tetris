//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Constants.h"
#include <list>


class Base_shape : public sf::Drawable{
//must deconstruct when all blocks are cleared
protected:
    std::list<sf::RectangleShape> _tetris_piece;
    sf::RectangleShape _r1;
    sf::RectangleShape _r2;
    sf::RectangleShape _r3;
    sf::RectangleShape _r4;
    sf::RectangleShape _r5;
// Some blocks have 5 parts

    sf::Vector2f _rotation_center;
    bool _placed;


public:
    void rotate_block();
    void gravity(sf::View*);
    void move(sf::View*);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //TILEMAP_BASE_SHAPE_H
