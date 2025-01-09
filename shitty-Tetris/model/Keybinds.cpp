//
// Created by tobia on 09.05.2024.
//

#include "Keybinds.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>

void Keybinds::assign_default(unsigned int player) {

    if (player == 0){ //solo game
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_clockwise = sf::Keyboard::Key::Up;
        _key_counter_clock = sf::Keyboard::Key::Z;
        _key_drop = sf::Keyboard::Key::Space;
        _key_hold = sf::Keyboard::Key::C;
    } else if (player == 1){
        _key_down = sf::Keyboard::Key::S;
        _key_right = sf::Keyboard::Key::D;
        _key_left = sf::Keyboard::Key::A;
        _key_clockwise = sf::Keyboard::Key::W;
        _key_counter_clock = sf::Keyboard::Key::Q;
        _key_drop = sf::Keyboard::Key::Tab;
        _key_hold = sf::Keyboard::Key::E;
    } else if (player == 2){
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_clockwise = sf::Keyboard::Key::Up;
        _key_counter_clock = sf::Keyboard::Key::RShift;
        _key_drop = sf::Keyboard::Key::Enter;
        _key_hold = sf::Keyboard::Key::Dash;
    }
}

void Keybinds::assign_key(Actions action, sf::Keyboard::Key keycode) {

    switch (action) {
        case Actions::Move_down:
            _key_down = keycode;
            break;
        case Actions::Move_right:
            _key_right = keycode;
            break;
        case Actions::Move_left:
            _key_left = keycode;
            break;
        case Actions::Rotate_clockwise:
            _key_clockwise = keycode;
            break;
        case Actions::Rotate_counter_clock:
            _key_counter_clock = keycode;
            break;
        case Actions::Drop:
            _key_drop = keycode;
            break;
        case Actions::Hold:
            _key_hold = keycode;
            break;
        case Actions::Nothing:
            break;
    }
}

void Keybinds::assign_joystick(unsigned int id) {
    _joystick_id = id;
    _using_gamepad = true;
}


Actions Keybinds::translate_key(sf::Keyboard::Key &key) const{
    // Key codes not constant, so switchcase not possible

    if (_using_gamepad){
        return Actions::Nothing;
    }

   if (key == _key_down){
       return Actions::Move_down;
   } else if (key == _key_right){
       return Actions::Move_right;
   } else if (key == _key_left){
       return Actions::Move_left;
   } else if (key == _key_clockwise){
       return Actions::Rotate_clockwise;
   } else if (key == _key_counter_clock){
       return Actions::Rotate_counter_clock;
   } else if (key == _key_drop){
       return Actions::Drop;
   } else if (key == _key_hold){
       return Actions::Hold;
   } else{
       return Actions::Nothing;
   }
}

Actions Keybinds::translate_joystick_button(unsigned int id, unsigned int button) const{

    if (!_using_gamepad){
        return Actions::Nothing;
    }

    if (id == _joystick_id && button == 2){
        return Actions::Rotate_clockwise;
    } else if (id == _joystick_id && button == 3){
        return Actions::Rotate_counter_clock;
    } else if (id == _joystick_id && button == 0){
        return Actions::Hold;
    } else if (id == _joystick_id && button == 1){
        return Actions::Drop;
    } else{
        return Actions::Nothing;
    }
}

Actions Keybinds::translate_joystick_move(unsigned int id, float x, float y) const{

    if (!_using_gamepad){
        return Actions::Nothing;
    }

    if (id == _joystick_id && y > 50){
        return Actions::Move_down;
    } else if (id == _joystick_id && x > 50){
        return Actions::Move_right;
    } else if (id == _joystick_id && x < -50){
        return Actions::Move_left;
    } else{
        return Actions::Nothing;
    }
}

bool Keybinds::joystick_centered(unsigned int id, float x, float y) const{
    if (_joystick_id == id && (x > -50 && x < 50) && (y > -50 && y < 50)){
        return true;
    }
    return false;
}


std::list<sf::Keyboard::Key> Keybinds::get_keybinds_list() {
    return std::list<sf::Keyboard::Key>
            {_key_down, _key_right, _key_left, _key_clockwise, _key_counter_clock, _key_drop, _key_hold};
}