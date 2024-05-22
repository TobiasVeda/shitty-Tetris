//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Game.h"
#include "Keybinds.h"
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <thread>

Process::Process() {
    _is_setup = true;
    _keybind_loop = 0;

    _game = new Game();
    _keybinds = new Keybinds;
    _ui = new UI();
    _tilemap = new Tilemap();
}

Process::~Process(){
    delete _game;
    delete _keybinds;
    delete _tilemap;
    delete _ui;
}

void Process::init(bool multiplayer) {
    static bool p1 = true;
    if (multiplayer && p1){
        _player = 1; // duo p1
        p1 = false;
    } else if(multiplayer && !p1){
        _player = 2; // duo p2
    } else{
        _player = 0;
    }

    _game->setup(_player);
    _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Setup);
}

void Process::run() {
    _is_setup = false;
}

bool Process::set_keybinds(sf::Keyboard::Key keycode) {

    if(keycode == sf::Keyboard::Key::F11){
        // Preventing assigning keys when maximizing.
        return true;
    }

    if (keycode == sf::Keyboard::Key::Enter && _keybind_loop <= 6){
        _keybinds->assign_default(_player);
        _keybind_loop = 7;
        return false;
    }

    if (_keybind_loop <= 6){
        switch (_keybind_loop) {
            case 0:
                _keybinds->assign_key(Constants::Move_down, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 1:
                _keybinds->assign_key(Constants::Move_right, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 2:
                _keybinds->assign_key(Constants::Move_left, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 3:
                _keybinds->assign_key(Constants::Rotate_clockwise, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 4:
                _keybinds->assign_key(Constants::Rotate_counter_clock, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 5:
                _keybinds->assign_key(Constants::Drop, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
            case 6:
                _keybinds->assign_key(Constants::Hold, keycode);
                _ui->set_key_string(keycode);
                _keybind_loop++;
                return true;
        }
    } else{
        return false;
    }
}

bool Process::set_joystick(unsigned int id) {

    if (!_joystick_assigned){
        _keybinds->assign_joystick(id);
        _joystick_assigned = true;
    }
    return false;
}


void Process::keyboard_event_handler(sf::Keyboard::Key key){
    _process_mutex.lock();

    if(!_is_dead) {
        _game->do_action(_keybinds->translate_key(key));
        _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);
    }

    _process_mutex.unlock();
}

void Process::joystick_button_handler(unsigned int id, unsigned int button){
    _process_mutex.lock();

    if(!_is_dead) {
        _game->do_action(_keybinds->translate_joystick_button(id, button));
        _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);
    }

    _process_mutex.unlock();
}

void Process::joystick_move_handler(unsigned int id, float x, float y){
    _process_mutex.lock();

    if(!_is_dead) {


        if (_joystick_ready){
            _game->do_action(_keybinds->translate_joystick_move(id, x, y));
            _joystick_ready = false;
        }
        if (_keybinds->joystick_centered(id, x, y)){
            _joystick_ready = true;
        }

        _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);
    }

    _process_mutex.unlock();
}


void Process::gravity_loop(bool &window_open) {
    while (_is_setup){
        if (!window_open){
            break;
        }
    };

    while (window_open) {
        _process_mutex.lock();

        _is_dead = _game->is_dead();

        if (_is_dead){
            _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::End);
        } else{
            _game->do_gametick_action();
            _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);
        }


        _process_mutex.unlock();

        auto delay = std::chrono::milliseconds((long long)_game->get_gravity_delay_ms());
        std::this_thread::sleep_for(delay);
    }
}


void Process::resize(float x, float y) {
    _game->resize(x, y);
}

void Process::display(sf::RenderWindow &window) {
    // sf::Drawable not used so that mutex can be locked/unlocked

    _process_mutex.lock();

    window.setView(_game->get_view());

    window.draw(*_tilemap);
    window.draw(*_game);
    window.draw(*_ui);

    _process_mutex.unlock();
}