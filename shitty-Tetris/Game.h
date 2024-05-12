//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include "pieces/Base_shape.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game : public sf::Drawable{
protected:
    static inline sf::RenderWindow _window;
    sf::View _view;
    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;

    Base_shape _player_controlled_block;
    std::vector<sf::RectangleShape> _block_stack;

    void set_bounds();

    void move_player(Constants::Directions);
    void rotate_player(Constants::Rotation_direction);
    void gravity();
    void drop_player();

    void try_lineclear();
    bool is_filled(sf::Vector2f&);
    void clear_row(float);
    void move_line_down(std::vector<int>&);

    void try_placing_player();
    void add_player_to_collection();

    bool player_intersects_with_stack();
    bool player_intersects_with_bounds();

    bool player_clear_to_move_down(bool auto_commit = false);
    bool player_clear_to_move_right(bool auto_commit = false);
    bool player_clear_to_move_left(bool auto_commit = false);
    bool player_clear_to_rotate_clockwise(bool auto_commit = false);
    bool player_clear_to_rotate_counter_clock(bool auto_commit = false);

public:
//    static void create_window();
    Game(int);
    void do_gametick_action();
    void do_action(Constants::Actions);
    static sf::RenderWindow& get_window();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_GAME_H
