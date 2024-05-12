//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <mutex>
#include "pieces/Base_shape.h"

class Game : public sf::Drawable{
protected:
    static inline sf::RenderWindow _window;
    Base_shape _player_controlled_block;
    sf::View _view;
    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;

    std::vector<sf::RectangleShape> _block_stack;

    void set_bounds();
    void move_line_down(std::vector<int>&);
    void clear_row(float);
    bool is_filled(sf::Vector2f&);

    void move_player(Constants::Directions);
    void rotate_player();
    void drop_player();

public:
//    static void create_window();
    Game(int);

    void add_player_to_collection();
    void try_lineclear();
    void do_gametick_action();
    void do_action(int);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

    void try_placing_player();
    void gravity();
    void try_lineclear();

    bool player_intersects_with_stack();
    bool player_intersects_with_bounds();

    bool player_clear_to_move_down(bool auto_commit = false);
    bool player_clear_to_move_right(bool auto_commit = false);
    bool player_clear_to_move_left(bool auto_commit = false);
};


#endif //SHITTY_TETRIS_GAME_H
