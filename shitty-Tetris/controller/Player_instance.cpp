//
// Created by tobia on 09.05.2024.
//

#include "Player_instance.h"
#include "../view/Tilemap.h"
#include "../model/Game.h"
#include "../model/Keybinds.h"
#include "../view/UI.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <thread>

Player_instance::Player_instance(bool multiplayer) {

    _keybind_loop = 0;
    _is_dead = false;
    _joystick_ready = true;
    _joystick_assigned = false;


    static bool p1 = true;
    if (multiplayer && p1){
        _player = 1; // duo p1
        p1 = false;
    } else if(multiplayer && !p1){
        _player = 2; // duo p2
    } else{
        _player = 0;
    }

    _game = new Game(_player);
    _keybinds = new Keybinds();
    _ui = new UI();
    _tilemap = new Tilemap();

    _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                _game->get_scoreboard(), Game_states::Setup);
}

Player_instance::~Player_instance(){
    delete _game;
    delete _keybinds;
    delete _tilemap;
    delete _ui;
}

bool Player_instance::set_keybinds(sf::Keyboard::Key keycode) {
    // Returns false when all keys assigned

    if(keycode == sf::Keyboard::Key::F11){
        // Preventing assigning keys when maximizing.
        return true;
    }

    if (keycode == sf::Keyboard::Key::Enter && _keybind_loop <= 6){
        _keybinds->assign_default(_player);
        _ui->set_all_keys_string(_keybinds->get_keybinds_list());
        _keybind_loop = 7;
        return false;
    }

    if (_keybind_loop <= 6){
        switch (_keybind_loop) {
            case 0:
                _keybinds->assign_key(Actions::Move_down, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 1:
                _keybinds->assign_key(Actions::Move_right, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 2:
                _keybinds->assign_key(Actions::Move_left, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 3:
                _keybinds->assign_key(Actions::Rotate_clockwise, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 4:
                _keybinds->assign_key(Actions::Rotate_counter_clock, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 5:
                _keybinds->assign_key(Actions::Drop, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 6:
                _keybinds->assign_key(Actions::Hold, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                // Returns false when all keys assigned
                return false;
        }
    } else{
        return false;
    }
} // Yes it does.

bool Player_instance::set_joystick(unsigned int id) {

    if (!_joystick_assigned){
        _keybinds->assign_joystick(id);
        _ui->set_joystick_string();
        _joystick_assigned = true;
    }
    return false;
}


void Player_instance::keyboard_event_handler(sf::Keyboard::Key key){

    if(!_is_dead) {
        _game->do_action(_keybinds->translate_key(key));
        _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                    _game->get_scoreboard(), Game_states::Run);
    }
}

void Player_instance::joystick_button_handler(unsigned int id, unsigned int button){

    if(!_is_dead) {
        _game->do_action(_keybinds->translate_joystick_button(id, button));
        _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                    _game->get_scoreboard(), Game_states::Run);
    }
}

void Player_instance::joystick_move_handler(unsigned int id, float x, float y){
    if(!_is_dead) {

        if (_joystick_ready){
            _game->do_action(_keybinds->translate_joystick_move(id, x, y));
            _joystick_ready = false;
        }
        if (_keybinds->joystick_centered(id, x, y)){
            _joystick_ready = true;
        }

        _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                    _game->get_scoreboard(), Game_states::Run);
    }
}

void Player_instance::set_end_state(End_states state) {
    switch (state) {
        case End_states::Winner:
            _ui->winner();
            break;
        case End_states::Loser:
            _ui->loser();
            break;
        case End_states::Tie:
            _ui->tie();
            break;
        case End_states::Game_over:
            break;
    }
}

bool Player_instance::is_dead() const{
    return _is_dead;
}

unsigned int Player_instance::get_score() const{
    return _game->get_score();
}


std::chrono::milliseconds Player_instance::gravity_tick() {

    _is_dead = _game->is_dead();

    if (_is_dead){
        _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                    _game->get_scoreboard(), Game_states::End);

    } else{
        _game->do_gametick_action();
        _ui->update(_game->get_held_type(), _game->get_3_next_types(),
                    _game->get_scoreboard(), Game_states::Run);
    }

    auto delay = std::chrono::milliseconds((long long)_game->get_gravity_delay_ms());
    return delay;

}


void Player_instance::resize(unsigned int x, unsigned int y) {
    _game->resize((float)x, (float)y);
}

//======================================public=======================================
//======================================private======================================

void Player_instance::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.setView(_game->get_view());

    target.draw(*_tilemap);
    target.draw(*_game);
    target.draw(*_ui);
}