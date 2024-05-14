//
// Created by tobia on 14.05.2024.
//

#ifndef SHITTY_TETRIS_UI_H
#define SHITTY_TETRIS_UI_H

#include <SFML/Graphics.hpp>

class UI : public sf::Drawable{
protected:
    sf::RectangleShape _hold_container;
    sf::RectangleShape _next_container;
public:
    UI();
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_UI_H
