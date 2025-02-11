//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include "pieces/Base_shape.h"
#include "Keybinds.h"
#include "Block_generator.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game : public sf::Drawable{
private:

    sf::View _view;

    // Needed for resize
    float _pos_x_view;
    float _pos_y_view;
    float _basesize_view_x;
    float _basesize_view_y;

    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;

    Block_generator *_generator;

    Base_shape *_player_controlled_block;
    Block_types _held_blocktype;
    bool _held_this_turn;
    std::vector<sf::RectangleShape> _block_stack;

    unsigned int _score;
    unsigned int _level;
    unsigned int _lines_cleared;
    bool _is_dead;

    void set_bounds();

    void move_player(Directions);
    void rotate_player(Rotation_direction);
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
    [[nodiscard]] unsigned int calculate_clear_points(int) const;
    [[nodiscard]] unsigned int calculate_move_points() const;
    [[nodiscard]] unsigned int calculate_drop_points() const;

    [[nodiscard]] bool player_intersects_with_stack();
    [[nodiscard]] bool player_intersects_with_bounds();

    bool player_clear_to_move_down(bool auto_commit = false);
    bool player_clear_to_move_right(bool auto_commit = false);
    bool player_clear_to_move_left(bool auto_commit = false);
    bool player_clear_to_rotate_clockwise(bool auto_commit = false);
    bool player_clear_to_rotate_counter_clock(bool auto_commit = false);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
    Game(unsigned int);
    ~Game();

    void do_action(Actions);
    void do_gametick_action();

    void resize(float, float);

    [[nodiscard]] Block_types get_held_type() const;
    [[nodiscard]] std::vector<Block_types> get_3_next_types() const;
    [[nodiscard]] std::vector<unsigned int> get_scoreboard() const;
    [[nodiscard]] unsigned int get_score() const;
    [[maybe_unused]] [[nodiscard]] unsigned int get_level() const;

    [[maybe_unused]] [[maybe_unused]] [[nodiscard]] unsigned int get_lines_cleared() const;
    [[nodiscard]] sf::View& get_view();
    [[nodiscard]] double get_gravity_delay_ms() const;
    [[nodiscard]] bool is_dead() const;
};


#endif //SHITTY_TETRIS_GAME_H
