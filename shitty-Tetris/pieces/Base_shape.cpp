//
// Created by tobia on 20.04.2024.
//
#include <SFML/Graphics.hpp>
#include "Base_shape.h"
#include "../Game.h"


bool Base_shape::is_clear_to_move_down() {

    for (auto& stack_block : *_game->get_stack()) {
        for (auto& stack_rectangle : stack_block) {
            for (auto& this_rectangle : this->_tetris_piece) {

                auto this_global_bound_1_down = this_rectangle.getGlobalBounds();
                this_global_bound_1_down.height += 1;

                bool will_collide_with_stack =
                        this_global_bound_1_down.intersects(stack_rectangle.getGlobalBounds());
                if (will_collide_with_stack){
                    return false;
                }

            }
        }
    }

    for (auto& i : _tetris_piece) {

        auto global_bound_1_down = i.getGlobalBounds();
        global_bound_1_down.height += 1;

        bool will_collide_with_bounds =
                global_bound_1_down.intersects(_game->get_bounds("down")->getGlobalBounds());
        if (will_collide_with_bounds){
            return false;
        }

    }

    return true;
}
bool Base_shape::is_clear_to_move_right() {

    for (auto& stack_block : *_game->get_stack()) {
        for (auto& stack_rectangle : stack_block) {
            for (auto& this_rectangle : this->_tetris_piece) {

                auto this_global_bound_1_right = this_rectangle.getGlobalBounds();
                this_global_bound_1_right.width += 1;

                bool will_collide_with_stack =
                        this_global_bound_1_right.intersects(stack_rectangle.getGlobalBounds());
                if (will_collide_with_stack){
                    return false;
                }

            }
        }
    }

    for (auto& i : _tetris_piece) {

        auto global_bound_1_right = i.getGlobalBounds();
        global_bound_1_right.width += 1;

        bool will_collide_with_bounds =
                global_bound_1_right.intersects(_game->get_bounds("right")->getGlobalBounds());
        if (will_collide_with_bounds){
            return false;
        }

    }

    return true;
}
bool Base_shape::is_clear_to_move_left() {

    for (auto& stack_block : *_game->get_stack()) {
        for (auto& stack_rectangle : stack_block) {
            for (auto& this_rectangle : this->_tetris_piece) {

                auto this_global_bound_1_left = this_rectangle.getGlobalBounds();
                this_global_bound_1_left.left -= 1;

                bool will_collide_with_stack =
                        this_global_bound_1_left.intersects(stack_rectangle.getGlobalBounds());
                if (will_collide_with_stack){
                    return false;
                }

            }
        }
    }

    for (auto& i : _tetris_piece) {

        auto global_bound_1_left = i.getGlobalBounds();
        global_bound_1_left.left -= 1;

        bool will_collide_with_bounds =
                global_bound_1_left.intersects(_game->get_bounds("left")->getGlobalBounds());
        if (will_collide_with_bounds){
            return false;
        }

    }

    return true;
}

std::list<sf::RectangleShape>* Base_shape::get_block_list() {
    return &_tetris_piece;
}

void Base_shape::rotate_block(){
    for(auto& i : _tetris_piece){
        i.rotate(90);
    }
}

void Base_shape::gravity() {
    bool next_pos_valid = is_clear_to_move_down();

    if (next_pos_valid) {
        for (auto& i : _tetris_piece) {
            i.move(Constants::gravity_strength);
        }
    }

};

void Base_shape::drop() {
    // Runs gravity tile_count_y number of times instantly to drop block
    for (int i = 0; i < Constants::tile_count_y; ++i) {
        gravity();
    }
}

void Base_shape::move(std::string dir) {
    bool next_pos_valid_down = is_clear_to_move_down();
    bool next_pos_valid_right = is_clear_to_move_right();
    bool next_pos_valid_left = is_clear_to_move_left();


    if (dir == "down" && next_pos_valid_down) {
        auto down = sf::Vector2f(0, (float)Constants::tilesize.y);
        for (auto& i : _tetris_piece) {
            i.move(down);
        }
    } else if (dir == "right" && next_pos_valid_right) {
        auto right = sf::Vector2f((float)Constants::tilesize.y, 0);
        for (auto& i : _tetris_piece) {
            i.move(right);
        }
    } else if (dir == "left" && next_pos_valid_left) {
        auto left = sf::Vector2f(-1 * (float)Constants::tilesize.y, 0);
        for (auto& i : _tetris_piece) {
            i.move(left);
        }
    }
}

void Base_shape::try_placing() {
    bool can_move = is_clear_to_move_down();
    if (!can_move){
        _placed = true;
    }
}
bool Base_shape::is_placed() const{
    return _placed;
}

void Base_shape::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for (auto& i : _tetris_piece){

        states.texture = &_sprite;
        target.draw(i, states);
    }
}
