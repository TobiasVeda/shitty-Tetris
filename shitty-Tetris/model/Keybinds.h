//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_KEYBINDS_H
#define SHITTY_TETRIS_KEYBINDS_H

#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <list>

class Keybinds {
private:
    unsigned int _joystick_id;
    bool _using_gamepad = false;

    sf::Keyboard::Key _key_down;
    sf::Keyboard::Key _key_right;
    sf::Keyboard::Key _key_left;
    sf::Keyboard::Key _key_clockwise;
    sf::Keyboard::Key _key_counter_clock;
    sf::Keyboard::Key _key_drop;
    sf::Keyboard::Key _key_hold;
public:
    void assign_default(unsigned int);
    void assign_key(Actions, sf::Keyboard::Key);
    void assign_joystick(unsigned int);

    [[nodiscard]] Actions translate_key(sf::Keyboard::Key&) const;
    [[nodiscard]] Actions translate_joystick_button(unsigned int, unsigned int) const;
    [[nodiscard]] Actions translate_joystick_move(unsigned int, float, float) const;

    [[nodiscard]] bool joystick_centered(unsigned int, float, float) const;

    [[nodiscard]] std::list<sf::Keyboard::Key> get_keybinds_list();
};


#endif //SHITTY_TETRIS_KEYBINDS_H
