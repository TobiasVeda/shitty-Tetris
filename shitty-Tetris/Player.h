//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_PLAYER_H
#define SHITTY_TETRIS_PLAYER_H

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"

class Player {
protected:
    int _player;
    int _score;
    bool _is_dead;
    sf::Keyboard::Key _key_down;
    sf::Keyboard::Key _key_right;
    sf::Keyboard::Key _key_left;
    sf::Keyboard::Key _key_rotate_clockwise;
    sf::Keyboard::Key _key_rotate_counter_clock;
    sf::Keyboard::Key _key_drop;

public:
    explicit Player(int);
    Constants::Actions keyboard_controller(bool);
};


#endif //SHITTY_TETRIS_PLAYER_H
