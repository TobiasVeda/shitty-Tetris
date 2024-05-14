//
// Created by tobia on 09.05.2024.
//

#include "Player.h"
#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"

Player::Player(int player) {
    _player = player;
    _is_dead = false;
    _score = 0;

    if (_player == 0){ //solo game
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_rotate_clockwise = sf::Keyboard::Key::Up;
        _key_rotate_counter_clock = sf::Keyboard::Key::Z;
        _key_drop = sf::Keyboard::Key::Space;
        _key_hold = sf::Keyboard::Key::C;
    } else if (_player == 1){
        _key_down = sf::Keyboard::Key::S;
        _key_right = sf::Keyboard::Key::D;
        _key_left = sf::Keyboard::Key::A;
        _key_rotate_clockwise = sf::Keyboard::Key::W;
        _key_rotate_counter_clock = sf::Keyboard::Key::Q;
        _key_drop = sf::Keyboard::Key::Tab;
        _key_hold = sf::Keyboard::Key::E;
    } else if (_player == 2){
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_rotate_clockwise = sf::Keyboard::Key::Up;
        _key_rotate_counter_clock = sf::Keyboard::Key::RShift;
        _key_drop = sf::Keyboard::Key::Enter;
        _key_hold = sf::Keyboard::Key::Dash;
    }
}

Constants::Actions Player::keyboard_controller(bool key_hold) {

    if (sf::Keyboard::isKeyPressed(_key_down)){
        return Constants::Move_down;
    }
    if (sf::Keyboard::isKeyPressed(_key_right)){
        return Constants::Move_right;
    }
    if (sf::Keyboard::isKeyPressed(_key_left)){
        return Constants::Move_left;
    }
    if (sf::Keyboard::isKeyPressed(_key_rotate_clockwise) && !key_hold){
        return Constants::Rotate_clockwise;
    } else if (sf::Keyboard::isKeyPressed(_key_rotate_counter_clock) && !key_hold){
        return Constants::Rotate_counter_clock;
    }
    if (sf::Keyboard::isKeyPressed(_key_drop) && !key_hold){
        return Constants::Drop;
    }
    if (sf::Keyboard::isKeyPressed(_key_hold)){
        return Constants::Hold;
    }
    return Constants::Nothing;
}