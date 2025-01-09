//
// Created by tobia on 20.05.2024.
//

#include "Main_menu.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Main_menu::Main_menu(sf::RenderWindow &window){
    _view.setSize(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
    _view.setCenter((float)window.getSize().x /2, (float)window.getSize().y /2);
    window.setView(_view);

    try{
        if (!_title_texture.loadFromFile(Constants::title_texture)) {
            throw std::exception("Unable to load menu main title");
        }
    } catch (std::exception& e){
        std::cerr <<e.what() <<std::endl;
    }

    construct_container();

    try{
        if(!_font.loadFromFile(Constants::font_name)){
            throw std::exception("Unable to load main menu font");
        }
    } catch (std::exception& e){
        std::cerr <<e.what() <<std::endl;
    }

    construct_text();

}


void Main_menu::resize(float x, float y) {

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

int Main_menu::test_click(sf::Vector2i mouse) {
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

//======================================public=======================================
//======================================private======================================

void Main_menu::construct_container(){

    _menu_container.setSize(sf::Vector2f(_view.getSize().x, _view.getSize().y));
    _menu_container.setPosition(0, 0);
    _menu_container.setFillColor(sf::Color(6, 18, 107));

    float value;
    _view.getSize().x > _view.getSize().y ? value = _view.getSize().y : value  = _view.getSize().x;




    _title.setSize(sf::Vector2f(value / 2.7, value / 4.5));
    _title.setPosition(
            (_view.getSize().x /2) - (_title.getSize().x /2),
            (_view.getSize().y / 10)
    );
    _title.setTexture(&_title_texture);

    float edge_offset = _view.getSize().x / 6.f;
    float top_offset = (_view.getSize().y / 3.f) * 1.5f;

    _solo_container.setSize(sf::Vector2f(value / 3.37, value / 9));
    _solo_container.setPosition(
            edge_offset,
            top_offset
    );
    _solo_container.setFillColor(sf::Color::Cyan);

    _duo_container.setSize(sf::Vector2f(value / 3.37,  value / 9));
    _duo_container.setPosition(
            (_view.getSize().x) - _duo_container.getSize().x - edge_offset,
            top_offset
    );
    _duo_container.setFillColor(sf::Color::Cyan);
}



void Main_menu::construct_text() {



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

    _cc.setCharacterSize(30);
    _cc.setFont(_font);
    _cc.setFillColor(sf::Color::White);
    _cc.setString("Tetris Theme - Korobeiniki - Arranged for Piano\n"
                        "by GregorQuendel -- \n"
                        "https://freesound.org/s/719393/ -- License: \n"
                        "Attribution NonCommercial 4.0");
    _cc.setPosition(
            10,
            _view.getSize().y - ((float)_cc.getCharacterSize() * 5)
    );
}


void Main_menu::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.setView(_view);

    target.draw(_menu_container, states);
    target.draw(_title, states);
    target.draw(_solo_container, states);
    target.draw(_duo_container, states);
    target.draw(_solo_text, states);
    target.draw(_duo_text, states);
    target.draw(_cc, states);
}