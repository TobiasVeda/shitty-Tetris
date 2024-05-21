//
// Created by tobia on 20.05.2024.
//

#include "Main_menu.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

Main_menu::Main_menu(sf::RenderWindow &window){
    _view.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    _view.setCenter(window.getSize().x /2, window.getSize().y /2);
    window.setView(_view);

    _title_texture.loadFromFile(Constants::title_texture);

    construct_container();
    construct_text();

}

void Main_menu::construct_container() {

    _menu_container.setSize(_view.getSize());
    _menu_container.setPosition(0, 0);
    _menu_container.setFillColor(sf::Color(6, 18, 107));

    _title.setSize(sf::Vector2f(Constants::tilesize.x * 10, Constants::tilesize.y * 6));
    _title.setPosition(
            (_view.getSize().x /2) - (_title.getSize().x /2),
            Constants::tilesize.y * 3
    );
    _title.setTexture(&_title_texture);

    int center_offset = Constants::tilesize.x * 8;

    _solo_container.setSize(sf::Vector2f(Constants::tilesize.x * 8, Constants::tilesize.y * 3));
    _solo_container.setPosition(
            (_view.getSize().x /2) - (_solo_container.getSize().x) - center_offset,
            Constants::tilesize.y * 15
    );
    _solo_container.setFillColor(sf::Color::Cyan);

    _duo_container.setSize(sf::Vector2f(Constants::tilesize.x * 8, Constants::tilesize.y * 3));
    _duo_container.setPosition(
            (_view.getSize().x /2) + center_offset,
            Constants::tilesize.y * 15
    );
    _duo_container.setFillColor(sf::Color::Cyan);
}

void Main_menu::construct_text() {
    _font.loadFromFile(Constants::font_name);

    _solo_text.setCharacterSize(50);
    _solo_text.setFont(_font);
    _solo_text.setFillColor(sf::Color::Black);
    _solo_text.setString("SINGLEPLAYER");
    _solo_text.setPosition(
            _solo_container.getPosition().x + 35,
            _solo_container.getPosition().y + 30
    );

    _duo_text.setCharacterSize(50);
    _duo_text.setFont(_font);
    _duo_text.setFillColor(sf::Color::Black);
    _duo_text.setString("MULTIPLAYER");
    _duo_text.setPosition(
            _duo_container.getPosition().x + 45,
            _duo_container.getPosition().y + 30
    );
}



void Main_menu::test_hover(sf::Vector2i mouse) {

    if (_solo_container.getGlobalBounds().contains((float)mouse.x, (float)mouse.y)){
        _solo_container.setFillColor(sf::Color::Yellow);
        _solo_text.setFillColor(sf::Color::White);
    } else if(_duo_container.getGlobalBounds().contains((float)mouse.x, (float)mouse.y)){
        _duo_container.setFillColor(sf::Color::Yellow);
        _duo_text.setFillColor(sf::Color::White);
    } else{
        _solo_container.setFillColor(sf::Color::Cyan);
        _solo_text.setFillColor(sf::Color::Black);
        _duo_container.setFillColor(sf::Color::Cyan);
        _duo_text.setFillColor(sf::Color::Black);
    }
}

int Main_menu::test_click(sf::Vector2i mouse){
    if (_solo_container.getGlobalBounds().contains((float)mouse.x, (float)mouse.y)){
        _solo_container.setFillColor(sf::Color::Red);
        _solo_text.setFillColor(sf::Color::Cyan);
        return 1;
    } else if(_duo_container.getGlobalBounds().contains((float)mouse.x, (float)mouse.y)){
        _duo_container.setFillColor(sf::Color::Red);
        _duo_text.setFillColor(sf::Color::Cyan);
        return 2;
    } else{
        return -1;
    }
}

void Main_menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_menu_container, states);
    target.draw(_title, states);
    target.draw(_solo_container);
    target.draw(_duo_container);
    target.draw(_solo_text);
    target.draw(_duo_text);
}