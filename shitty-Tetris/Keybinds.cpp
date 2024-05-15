//
// Created by tobia on 09.05.2024.
//

#include "Keybinds.h"
#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"

Keybinds::Keybinds(int player) {
    _player = player;

    if (_player == 0){ //solo game
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_clockwise = sf::Keyboard::Key::Up;
        _key_counter_clock = sf::Keyboard::Key::Z;
        _key_drop = sf::Keyboard::Key::Space;
        _key_hold = sf::Keyboard::Key::C;
    } else if (_player == 1){
        _key_down = sf::Keyboard::Key::S;
        _key_right = sf::Keyboard::Key::D;
        _key_left = sf::Keyboard::Key::A;
        _key_clockwise = sf::Keyboard::Key::W;
        _key_counter_clock = sf::Keyboard::Key::Q;
        _key_drop = sf::Keyboard::Key::Tab;
        _key_hold = sf::Keyboard::Key::E;
    } else if (_player == 2){
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_clockwise = sf::Keyboard::Key::Up;
        _key_counter_clock = sf::Keyboard::Key::RShift;
        _key_drop = sf::Keyboard::Key::Enter;
        _key_hold = sf::Keyboard::Key::Dash;
    }
}

sf::Keyboard::Key Keybinds::get_keybind(Constants::Actions action){

    switch (action) {
        case Constants::Move_down:
            return _key_down;
        case Constants::Move_right:
            return _key_right;
        case Constants::Move_left:
            return _key_left;
        case Constants::Rotate_clockwise:
            return _key_clockwise;
        case Constants::Rotate_counter_clock:
            return _key_counter_clock;
        case Constants::Drop:
            return _key_drop;
        case Constants::Hold:
            return _key_hold;
    }
}
