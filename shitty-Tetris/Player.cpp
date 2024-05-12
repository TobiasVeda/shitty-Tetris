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
        _key_rotate = sf::Keyboard::Key::Up;
        _key_drop = sf::Keyboard::Key::Space;
    } else if (_player == 1){
        _key_down = sf::Keyboard::Key::S;
        _key_right = sf::Keyboard::Key::D;
        _key_left = sf::Keyboard::Key::A;
        _key_rotate = sf::Keyboard::Key::W;
        _key_drop = sf::Keyboard::Key::X;
    } else if (_player == 2){
        _key_down = sf::Keyboard::Key::Down;
        _key_right = sf::Keyboard::Key::Right;
        _key_left = sf::Keyboard::Key::Left;
        _key_rotate = sf::Keyboard::Key::Up;
        _key_drop = sf::Keyboard::Key::Space;
    }
}

void Player::keyboard_controller(Base_shape *block, bool key_hold) {
//    return action, base shape

    //Base_shape::move only allows one action per call (else if, not just if)
    //Controller allows multiple, but only one is performed at a time, thus clipping into corners is impossible
    //(or clipping was unintentionally fixed when collision detection was changed¯\_(ツ)_/¯)
    if (sf::Keyboard::isKeyPressed(_key_down)){
        block->move("down");
    }
    if (sf::Keyboard::isKeyPressed(_key_right)){
        block->move("right");
    }
    if (sf::Keyboard::isKeyPressed(_key_left)){
        block->move("left");
    }
    if (sf::Keyboard::isKeyPressed(_key_rotate) && !key_hold){
        block->rotate_block();
    }
    if (sf::Keyboard::isKeyPressed(_key_drop) && !key_hold){
        block->drop();
    }

}