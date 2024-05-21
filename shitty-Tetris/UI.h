//
// Created by tobia on 14.05.2024.
//

#ifndef SHITTY_TETRIS_UI_H
#define SHITTY_TETRIS_UI_H

#include <SFML/Graphics.hpp>
#include "pieces/Base_shape.h"
#include "Constants.h"
#include <vector>

class UI : public sf::Drawable{
protected:
    Constants::Game_states _state;

    sf::Font _font;
    sf::Text _score;
    sf::Text _level;
    sf::Text _lines;
    sf::Text _n_score;
    sf::Text _n_level;
    sf::Text _n_lines;

    sf::Text _hold_header;
    sf::Text _next_header;

    Base_shape *_hold;
    Base_shape *_next1;
    Base_shape *_next2;
    Base_shape *_next3;

    sf::RectangleShape _hold_container;
    sf::RectangleShape _next_container;

    sf::RectangleShape _greyout;
    sf::Text _key_description;
    sf::Text _keybinds;
    std::string _string_keybinds;

    sf::Text _game_over;

    bool construct_text();
    void construct_container();
    std::string keycode_to_string(sf::Keyboard::Key);
public:
    UI();
    ~UI();
    void update(Constants::Block_types, std::vector<int>, Constants::Game_states);
    void set_key_string(sf::Keyboard::Key);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_UI_H
