//
// Created by tobia on 14.05.2024.
//

#include "UI.h"
#include "Constants.h"
#include "Block_bag.h"

bool UI::construct_text() {
    _font.loadFromFile(Constants::font_name);

    _score.setFont(_font);
    _level.setFont(_font);
    _lines.setFont(_font);
    _n_score.setFont(_font);
    _n_level.setFont(_font);
    _n_lines.setFont(_font);

    _hold_header.setFont(_font);
    _next_header.setFont(_font);

    _score.setString("SCORE:");
    _level.setString("LEVEL:");
    _lines.setString("LINES:");
    _n_score.setString("0");
    _n_level.setString("1");
    _n_lines.setString("0");

    _hold_header.setString("HOLD");
    _next_header.setString("NEXT");

    _score.setCharacterSize(30);
    _level.setCharacterSize(30);
    _lines.setCharacterSize(30);
    _n_score.setCharacterSize(30);
    _n_level.setCharacterSize(30);
    _n_lines.setCharacterSize(30);

    _hold_header.setCharacterSize(30);
    _next_header.setCharacterSize(30);

    _score.setFillColor(sf::Color::Black);
    _level.setFillColor(sf::Color::Black);
    _lines.setFillColor(sf::Color::Black);
    _n_score.setFillColor(sf::Color::Black);
    _n_level.setFillColor(sf::Color::Black);
    _n_lines.setFillColor(sf::Color::Black);

    _hold_header.setFillColor(sf::Color::Black);
    _next_header.setFillColor(sf::Color::Black);

    _score.setPosition(405, 0);
    _level.setPosition(405, 30);
    _lines.setPosition(405, 60);
    _n_score.setPosition(485, 0);
    _n_level.setPosition(485, 30);
    _n_lines.setPosition(485, 60);

    _hold_header.setPosition(470, 100);
    _next_header.setPosition(470, 280);

//    return return_value;
    return true;
}

void UI::construct_container(){
    _hold_container.setOutlineColor(sf::Color::Black);
    _hold_container.setOutlineThickness(2);

    _next_container.setOutlineColor(sf::Color::Black);
    _next_container.setOutlineThickness(2);

    _hold_container.setSize(sf::Vector2f(
            180 - 4,
            180 - 40 - 4
    ));

    _next_container.setSize(sf::Vector2f(
            180 - 4,
            438
    ));

    _hold_container.setPosition(
            400 + 10 ,
            0 + 4 + 80 + 20
    );

    _next_container.setPosition(
            400 + 10,
            180 - 40 - 4 + 0 + 4 + 80 + 20 + 40
    );

}

void UI::load(){

    construct_text();
    construct_container();

}

void UI::update(Constants::Block_types hold_type, std::vector<int> scoreboard){
    _hold = Block_bag::get_new_block(hold_type);
    _next1 = Block_bag::get_new_block(Block_bag::get_next_vector()[0]);
    _next2 = Block_bag::get_new_block(Block_bag::get_next_vector()[1]);
    _next3 = Block_bag::get_new_block(Block_bag::get_next_vector()[2]);

    _hold.set_position(sf::Vector2f(500, 160));
    _next1.set_position(sf::Vector2f(500, 380));
    _next2.set_position(sf::Vector2f(500, 500));
    _next3.set_position(sf::Vector2f(500, 620));

    _n_score.setString(std::to_string(scoreboard[0]));
    _n_level.setString(std::to_string(scoreboard[1]));
    _n_lines.setString(std::to_string(scoreboard[2]));
}

void UI::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    target.draw(_hold_container, states);
    target.draw(_next_container, states);
    target.draw(_score, states);
    target.draw(_level, states);
    target.draw(_lines, states);
    target.draw(_n_score, states);
    target.draw(_n_level, states);
    target.draw(_n_lines, states);
    target.draw(_hold_header, states);
    target.draw(_next_header, states);
    target.draw(_hold, states);
    target.draw(_next1, states);
    target.draw(_next2, states);
    target.draw(_next3, states);
}