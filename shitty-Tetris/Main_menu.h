//
// Created by tobia on 20.05.2024.
//

#ifndef SHITTY_TETRIS_MAIN_MENU_H
#define SHITTY_TETRIS_MAIN_MENU_H

#include "Constants.h"
#include <SFML/Graphics.hpp>

class Main_menu : public sf::Drawable{
protected:
    sf::View _view;
    sf::RectangleShape _menu_container;
    sf::RectangleShape _title;
    sf::RectangleShape _solo_container;
    sf::RectangleShape _duo_container;

    sf::Font _font;
    sf::Text _solo_text;
    sf::Text _duo_text;

    sf::Texture _title_texture;

    void construct_container();
    void construct_text();
public:
    Main_menu(sf::RenderWindow&);
    void test_hover(sf::Vector2i);
    int test_click(sf::Vector2i);
    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_MAIN_MENU_H
