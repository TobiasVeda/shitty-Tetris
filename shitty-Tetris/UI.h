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
    sf::Font _font;
    sf::Text _score;
    sf::Text _level;
    sf::Text _lines;
    sf::Text _n_score;
    sf::Text _n_level;
    sf::Text _n_lines;

    sf::Text _hold_header;
    sf::Text _next_header;

    Base_shape _hold;
    Base_shape _next1;
    Base_shape _next2;
    Base_shape _next3;

    sf::RectangleShape _hold_container;
    sf::RectangleShape _next_container;

    bool construct_text();
    void construct_container();
public:
    void load();
    void update(Constants::Block_types, std::vector<int>);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_UI_H
