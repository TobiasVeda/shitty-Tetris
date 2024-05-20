//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_KEYBINDS_H
#define SHITTY_TETRIS_KEYBINDS_H

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "Constants.h"

class Keybinds {
protected:
    sf::Keyboard::Key _key_down;
    sf::Keyboard::Key _key_right;
    sf::Keyboard::Key _key_left;
    sf::Keyboard::Key _key_clockwise;
    sf::Keyboard::Key _key_counter_clock;
    sf::Keyboard::Key _key_drop;
    sf::Keyboard::Key _key_hold;
public:
    void assign_key(Constants::Actions, sf::Keyboard::Key);
    void assign_default(int);
    Constants::Actions translate_key(sf::Keyboard::Key&);
};


#endif //SHITTY_TETRIS_KEYBINDS_H
