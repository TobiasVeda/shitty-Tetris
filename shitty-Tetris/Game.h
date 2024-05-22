//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include "pieces/Base_shape.h"
#include "Keybinds.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game : public sf::Drawable{
protected:

    sf::View _view;
    float _pos_x_view;
    float _pos_y_view;
    float _basesize_view_x;
    float _basesize_view_y;

    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;

    Base_shape *_player_controlled_block;
    Constants::Block_types _held_blocktype;
    bool _held_this_turn;
    std::vector<sf::RectangleShape> _block_stack;

    int _score;
    int _level;
    int _lines_cleared;
    bool _is_dead;

    void set_bounds();

    void move_player(Constants::Directions);
    void rotate_player(Constants::Rotation_direction);
    bool gravity();
    void drop_player();
    void hold_player();

    void try_lineclear();
    [[nodiscard]] bool is_filled(sf::Vector2f&);
    void clear_row(float);
    void move_lines_down(std::vector<int>&);

    void try_placing_player();
    void add_player_to_collection();
    void new_round();
    void try_death();

    void try_levelup();
    [[nodiscard]] int calculate_clear_points(int);
    [[nodiscard]] int calculate_move_points();
    [[nodiscard]] int calculate_drop_points();

    [[nodiscard]] bool player_intersects_with_stack();
    [[nodiscard]] bool player_intersects_with_bounds();

    bool player_clear_to_move_down(bool auto_commit = false);
    bool player_clear_to_move_right(bool auto_commit = false);
    bool player_clear_to_move_left(bool auto_commit = false);
    bool player_clear_to_rotate_clockwise(bool auto_commit = false);
    bool player_clear_to_rotate_counter_clock(bool auto_commit = false);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
    Game() = default;
    ~Game();
    void setup(int);

    void do_action(Constants::Actions);
    void do_gametick_action();

    void resize(float, float);

    [[nodiscard]] Constants::Block_types get_held_type() const;
    [[nodiscard]] std::vector<int> get_scoreboard() const;
    [[nodiscard]] sf::View& get_view();
    [[nodiscard]] double get_gravity_delay_ms() const;
    [[nodiscard]] bool is_dead() const;
};


#endif //SHITTY_TETRIS_GAME_H
