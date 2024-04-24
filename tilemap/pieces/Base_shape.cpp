//
// Created by tobia on 20.04.2024.
//
#include <SFML/Graphics.hpp>
#include "Base_shape.h"




    void Base_shape::rotate_block(){
//        auto cleared = sf::Vector2f(-1, -1);
//
//        if (r1.getPosition() != cleared) {
//            r1.setOrigin(sf::Vector2f(0, 0));
//            r1.rotate(90);
//        }
//        if (r2.getPosition() != cleared) {
//            r2.setOrigin(sf::Vector2f(0, 0));
//            r2.rotate(90);
//        }
//        if (r3.getPosition() != cleared){
//            r3.setOrigin(sf::Vector2f(0,0));
//            r3.rotate(90);
//        }
//
//        if (r4.getPosition() != cleared){
//            r4.setOrigin(sf::Vector2f(0,0));
//            r4.rotate(90);
//        }
//
//        if (r5.getPosition() != cleared){
//            r5.setOrigin(sf::Vector2f(0,0));
//            r5.rotate(90);
//        }

//order of set position and origin can give issues maybe
    }

    void Base_shape::gravity(sf::View *view) {
        while (true){
            auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);
            bool next_pos_valid = false;

            // To be considered out of bounds and therefore prevent gravity,
            // a rectangle must not be cleared and its next move must set its position outside the view
            for (const auto& i : _tetris_piece) {
                bool is_oob = i->getPosition().y + (tilesize_f.y * 2) > view->getSize().y;

                if (!is_oob){
                    next_pos_valid = true;
                }else{
                    next_pos_valid = false;
                    // default should be false
                }
            }

            if (next_pos_valid) {
                for (auto i : _tetris_piece) {
                    i->move(Constants::gravity_strength);
                }
            }
            Constants::wait_game_tick();

            if (!next_pos_valid){
                _placed = true;
            }
        }
    };

void Base_shape::move(sf::View *view) {
    while (true){

        auto tilesize_f = static_cast<sf::Vector2f>(Constants::tilesize);
        auto cleared = sf::Vector2f(-1, -1);
        bool key_down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
        bool key_right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
        bool key_left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
        bool next_pos_valid_down = false;
        bool next_pos_valid_right = false;
        bool next_pos_valid_left = false;

        for (const auto& i : _tetris_piece) { // collision down
            bool is_oob_down = i->getPosition().y + (tilesize_f.y * 2) > view->getSize().y;

            if (!is_oob_down){
                next_pos_valid_down = true;
            }else{
                next_pos_valid_down = false;
                break;
                // default should be false
            }
        }
        for (const auto& i : _tetris_piece) { // collision right
            bool is_oob_right = i->getPosition().x + (tilesize_f.x * 2) > view->getSize().x;

            if (!is_oob_right){
                next_pos_valid_right = true;
            }else{
                next_pos_valid_right = false;
                break;
                // default should be false
            }
        }
        for (const auto& i : _tetris_piece) { // collision left
            bool is_oob_left = i->getPosition().x <= 0;

            if (!is_oob_left){
                next_pos_valid_left = true;
            }else{
                next_pos_valid_left = false;
                break;
                // default should be false
            }
        }


        if (key_down && next_pos_valid_down) {
            for (auto& i : _tetris_piece) {
                i->move(sf::Vector2f(0, (float)Constants::tilesize.y));
            }
        }
        if (key_right && next_pos_valid_right) {
            for (auto& i : _tetris_piece) {
                i->move(sf::Vector2f((float)Constants::tilesize.y, 0));
            }
        }
        if (key_left && next_pos_valid_left) {
            for (auto& i : _tetris_piece) {
                i->move(sf::Vector2f(-1 * (float)Constants::tilesize.y, 0));
            }
        }
        Constants::wait_movement_speed();
    }

};
bool Base_shape::is_placed() const{
    return _placed;
}

    void Base_shape::draw(sf::RenderTarget& target, sf::RenderStates states) const{
        for (auto& i : _tetris_piece) {
            target.draw(*i, states);
        }
    }
