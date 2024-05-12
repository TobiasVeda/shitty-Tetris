//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_BASE_SHAPE_H
#define TILEMAP_BASE_SHAPE_H

#include <SFML/Graphics.hpp>
#include "../Tilemap.h"
#include "../Constants.h"
#include "../Game.h"
#include <list>


class Base_shape : public sf::Drawable, public sf::Transformable{
//must deconstruct when all blocks are cleared

protected:
    std::list<sf::RectangleShape> _tetris_piece;
    sf::RectangleShape _r1;
    sf::RectangleShape _r2;
    sf::RectangleShape _r3;
    sf::RectangleShape _r4;

    Game *_game;

    sf::Transform _transform;
    sf::Texture _sprite;
    bool _placed;

    bool is_clear_to_move_down();
    bool is_clear_to_move_right();
    bool is_clear_to_move_left();

public:
    std::list<sf::RectangleShape>* get_block_list();
    void rotate_block();
    void gravity();
    void drop();
    void move(std::string);
    [[nodiscard]] bool is_placed() const;
    void try_placing();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};

#endif //TILEMAP_BASE_SHAPE_H
