//
// Created by tobia on 14.05.2024.
//

#include "UI.h"
#include "../Constants.h"
#include "../Block_bag.h"
#include <SFML/Graphics.hpp>

UI::UI(){
    _state = Constants::Setup;
    construct_text();
    construct_container();
}
UI::~UI() noexcept {
    delete _hold;
    delete _next1;
    delete _next2;
    delete _next3;
}

void UI::winner() {
    _game_over.setString("WINNER!");
}

void UI::loser() {
    _game_over.setString("LOSER");
}

void UI::tie() {
    _game_over.setString("TIE");
}


void UI::update(Constants::Block_types hold_type, std::vector<unsigned int> scoreboard, Constants::Game_states state){
    _state = state;

    if (hold_type != Constants::Ndef){
        _hold = Block_bag::get_new_block(hold_type);
        _hold->set_position(sf::Vector2f(500, 160));
    } else{
        _hold = nullptr;
    }
    _next1 = Block_bag::get_new_block(Block_bag::get_next_vector()[0]);
    _next2 = Block_bag::get_new_block(Block_bag::get_next_vector()[1]);
    _next3 = Block_bag::get_new_block(Block_bag::get_next_vector()[2]);

    _next1->set_position(sf::Vector2f(500, 380));
    _next2->set_position(sf::Vector2f(500, 500));
    _next3->set_position(sf::Vector2f(500, 620));

    _n_score.setString(std::to_string(scoreboard[0]));
    _n_level.setString(std::to_string(scoreboard[1]));
    _n_lines.setString(std::to_string(scoreboard[2]));

    if (_state == Constants::End){
        _score.setCharacterSize(40);
        _level.setCharacterSize(40);
        _lines.setCharacterSize(40);
        _n_score.setCharacterSize(40);
        _n_level.setCharacterSize(40);
        _n_lines.setCharacterSize(40);

        _score.setPosition(160, 220);
        _level.setPosition(160, 270);
        _lines.setPosition(160, 320);
        _n_score.setPosition(280, 220);
        _n_level.setPosition(280, 270);
        _n_lines.setPosition(280, 320);
    }

}

void UI::set_all_keys_string(const std::list<sf::Keyboard::Key>& key_list) {
    _string_keybinds = "";
    for (auto& key : key_list) {
        _string_keybinds.append(keycode_to_string(key));
        _string_keybinds.append("\n");
    }
    _keybinds.setString(_string_keybinds);
}

void UI::set_key_string(sf::Keyboard::Key key) {
    _string_keybinds.append(keycode_to_string(key));
    _string_keybinds.append("\n");
    _keybinds.setString(_string_keybinds);
}

void UI::set_joystick_string() {
    _keybinds.setString("STICK DOWN\nSTICK RIGHT\nSTICK LEFT\nB\nY\nA\nX\n");
}

//======================================public=======================================
//======================================private======================================

void UI::construct_text() {
    if(!_font.loadFromFile(Constants::font_name)){
        throw std::exception("Unable to load UI font");
    }

    _score.setFont(_font);
    _level.setFont(_font);
    _lines.setFont(_font);
    _n_score.setFont(_font);
    _n_level.setFont(_font);
    _n_lines.setFont(_font);

    _hold_header.setFont(_font);
    _next_header.setFont(_font);

    _game_over.setFont(_font);

    _score.setString("SCORE:");
    _level.setString("LEVEL:");
    _lines.setString("LINES:");
    _n_score.setString("0");
    _n_level.setString("1");
    _n_lines.setString("0");

    _hold_header.setString("HOLD");
    _next_header.setString("NEXT");

    _game_over.setString("GAME OVER");

    _score.setCharacterSize(30);
    _level.setCharacterSize(30);
    _lines.setCharacterSize(30);
    _n_score.setCharacterSize(30);
    _n_level.setCharacterSize(30);
    _n_lines.setCharacterSize(30);

    _hold_header.setCharacterSize(30);
    _next_header.setCharacterSize(30);

    _game_over.setCharacterSize(45);

    _score.setFillColor(sf::Color::Black);
    _level.setFillColor(sf::Color::Black);
    _lines.setFillColor(sf::Color::Black);
    _n_score.setFillColor(sf::Color::Black);
    _n_level.setFillColor(sf::Color::Black);
    _n_lines.setFillColor(sf::Color::Black);

    _hold_header.setFillColor(sf::Color::Black);
    _next_header.setFillColor(sf::Color::Black);

    _game_over.setFillColor(sf::Color::Black);

    _score.setPosition(405, 0);
    _level.setPosition(405, 30);
    _lines.setPosition(405, 60);
    _n_score.setPosition(485, 0);
    _n_level.setPosition(485, 30);
    _n_lines.setPosition(485, 60);

    _hold_header.setPosition(470, 100);
    _next_header.setPosition(470, 280);

    _game_over.setPosition(140, 100);

    _key_description.setFont(_font);
    _keybinds.setFont(_font);

    _key_description.setString("PRESS ENTER FOR DEAFULT KEYBINDS\n"
                               "OR USE CONTROLLER\n\n"
                               "MOVE DOWN:\nMOVE RIGHT:\nMOVE LEFT:\nROTATE CLOCKWISE:\nROTATE COUNTER-CLOCK:\n"
                               "DROP BLOCK:\nHOLD BLOCK:");
    _key_description.setCharacterSize(35);
    _keybinds.setCharacterSize(35);

    _key_description.setFillColor(sf::Color::Black);
    _keybinds.setFillColor(sf::Color::Black);

    _key_description.setPosition(10, 40);
    _keybinds.setPosition(320, 168);
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



    _greyout.setSize(sf::Vector2f(600, 720));
    _greyout.setPosition(0, 0);
    _greyout.setFillColor(sf::Color(150, 150, 150, 240));

}


void UI::draw(sf::RenderTarget &target, sf::RenderStates states) const{

    target.draw(_hold_container, states);
    target.draw(_next_container, states);
    if (_state != Constants::End) {
        // Prevents double draw on death
        target.draw(_score, states);
        target.draw(_level, states);
        target.draw(_lines, states);
        target.draw(_n_score, states);
        target.draw(_n_level, states);
        target.draw(_n_lines, states);
    }
    target.draw(_hold_header, states);
    target.draw(_next_header, states);
    if (_hold != nullptr){
        target.draw(*_hold, states);
    }
    target.draw(*_next1, states);
    target.draw(*_next2, states);
    target.draw(*_next3, states);

    if (_state == Constants::Setup){
        target.draw(_greyout, states);
        target.draw(_key_description, states);
        target.draw(_keybinds, states);
    } else if (_state == Constants::End){
        target.draw(_greyout, states);
        target.draw(_game_over, states);
        target.draw(_score, states);
        target.draw(_level, states);
        target.draw(_lines, states);
        target.draw(_n_score, states);
        target.draw(_n_level, states);
        target.draw(_n_lines, states);
    }
}

//======================================private======================================
//======================================public=======================================

std::string UI::keycode_to_string(sf::Keyboard::Key keycode){
    switch (keycode) {
        case sf::Keyboard::A: return "A";
        case sf::Keyboard::B: return "B";
        case sf::Keyboard::C: return "C";
        case sf::Keyboard::D: return "D";
        case sf::Keyboard::E: return "E";
        case sf::Keyboard::F: return "F";
        case sf::Keyboard::G: return "G";
        case sf::Keyboard::H: return "H";
        case sf::Keyboard::I: return "I";
        case sf::Keyboard::J: return "J";
        case sf::Keyboard::K: return "K";
        case sf::Keyboard::L: return "L";
        case sf::Keyboard::M: return "M";
        case sf::Keyboard::N: return "N";
        case sf::Keyboard::O: return "O";
        case sf::Keyboard::P: return "P";
        case sf::Keyboard::Q: return "Q";
        case sf::Keyboard::R: return "R";
        case sf::Keyboard::S: return "S";
        case sf::Keyboard::T: return "T";
        case sf::Keyboard::U: return "U";
        case sf::Keyboard::V: return "V";
        case sf::Keyboard::W: return "W";
        case sf::Keyboard::X: return "X";
        case sf::Keyboard::Y: return "Y";
        case sf::Keyboard::Z: return "Z";
        case sf::Keyboard::Num0: return "0";
        case sf::Keyboard::Num1: return "1";
        case sf::Keyboard::Num2: return "2";
        case sf::Keyboard::Num3: return "3";
        case sf::Keyboard::Num4: return "4";
        case sf::Keyboard::Num5: return "5";
        case sf::Keyboard::Num6: return "6";
        case sf::Keyboard::Num7: return "7";
        case sf::Keyboard::Num8: return "8";
        case sf::Keyboard::Num9: return "9";
        case sf::Keyboard::Escape: return "Escape";
        case sf::Keyboard::LControl: return "Left Control";
        case sf::Keyboard::LShift: return "Left Shift";
        case sf::Keyboard::LAlt: return "Left Alt";
        case sf::Keyboard::LSystem: return "Left System";
        case sf::Keyboard::RControl: return "Right Control";
        case sf::Keyboard::RShift: return "Right Shift";
        case sf::Keyboard::RAlt: return "Right Alt";
        case sf::Keyboard::RSystem: return "Right System";
        case sf::Keyboard::Menu: return "Menu";
        case sf::Keyboard::LBracket: return "[";
        case sf::Keyboard::RBracket: return "]";
        case sf::Keyboard::SemiColon: return ";";
        case sf::Keyboard::Comma: return ",";
        case sf::Keyboard::Period: return ".";
        case sf::Keyboard::Quote: return "'";
        case sf::Keyboard::Slash: return "/";
        case sf::Keyboard::BackSlash: return "\\";
        case sf::Keyboard::Tilde: return "~";
        case sf::Keyboard::Equal: return "=";
        case sf::Keyboard::Dash: return "-";
        case sf::Keyboard::Space: return "Space";
        case sf::Keyboard::Return: return "Return";
        case sf::Keyboard::BackSpace: return "Backspace";
        case sf::Keyboard::Tab: return "Tab";
        case sf::Keyboard::PageUp: return "Page Up";
        case sf::Keyboard::PageDown: return "Page Down";
        case sf::Keyboard::End: return "End";
        case sf::Keyboard::Home: return "Home";
        case sf::Keyboard::Insert: return "Insert";
        case sf::Keyboard::Delete: return "Delete";
        case sf::Keyboard::Add: return "+";
        case sf::Keyboard::Subtract: return "-";
        case sf::Keyboard::Multiply: return "*";
        case sf::Keyboard::Divide: return "/";
        case sf::Keyboard::Left: return "Left Arrow";
        case sf::Keyboard::Right: return "Right Arrow";
        case sf::Keyboard::Up: return "Up Arrow";
        case sf::Keyboard::Down: return "Down Arrow";
        case sf::Keyboard::Numpad0: return "Numpad 0";
        case sf::Keyboard::Numpad1: return "Numpad 1";
        case sf::Keyboard::Numpad2: return "Numpad 2";
        case sf::Keyboard::Numpad3: return "Numpad 3";
        case sf::Keyboard::Numpad4: return "Numpad 4";
        case sf::Keyboard::Numpad5: return "Numpad 5";
        case sf::Keyboard::Numpad6: return "Numpad 6";
        case sf::Keyboard::Numpad7: return "Numpad 7";
        case sf::Keyboard::Numpad8: return "Numpad 8";
        case sf::Keyboard::Numpad9: return "Numpad 9";
        case sf::Keyboard::F1: return "F1";
        case sf::Keyboard::F2: return "F2";
        case sf::Keyboard::F3: return "F3";
        case sf::Keyboard::F4: return "F4";
        case sf::Keyboard::F5: return "F5";
        case sf::Keyboard::F6: return "F6";
        case sf::Keyboard::F7: return "F7";
        case sf::Keyboard::F8: return "F8";
        case sf::Keyboard::F9: return "F9";
        case sf::Keyboard::F10: return "F10";
        case sf::Keyboard::F11: return "F11";
        case sf::Keyboard::F12: return "F12";
        case sf::Keyboard::F13: return "F13";
        case sf::Keyboard::F14: return "F14";
        case sf::Keyboard::F15: return "F15";
        case sf::Keyboard::Pause: return "Pause";
        default: return "Unknown";
    }
}