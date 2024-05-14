//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include "pieces/Base_shape.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Constants.h"

class Game : public sf::Drawable{
protected:
    sf::View _view;
    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;

    Base_shape test;
    Base_shape _player_controlled_block;
    Constants::Block_types _held_block;


    bool _held_this_turn;
    std::vector<sf::RectangleShape> _block_stack;

    void set_bounds();

    void move_player(Constants::Directions);
    void rotate_player(Constants::Rotation_direction);
    void gravity();
    void drop_player();
    void hold_player();

    void try_lineclear();
    bool is_filled(sf::Vector2f&);
    void clear_row(float);
    void move_line_down(std::vector<int>&);

    void try_placing_player();
    void add_player_to_collection();
    void new_round();

    bool player_intersects_with_stack();
    bool player_intersects_with_bounds();

    bool player_clear_to_move_down(bool auto_commit = false);
    bool player_clear_to_move_right(bool auto_commit = false);
    bool player_clear_to_move_left(bool auto_commit = false);
    bool player_clear_to_rotate_clockwise(bool auto_commit = false);
    bool player_clear_to_rotate_counter_clock(bool auto_commit = false);
public:
    Game(sf::RenderWindow&, int);
    void do_gametick_action();
    void do_action(Constants::Actions);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_GAME_H
