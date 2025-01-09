//
// Created by tobia on 22.05.2024.
//

#include "Process.h"
#include "../view/Audio.h"
#include "../view/Main_menu.h"
#include "../Enumerations.h"
#include <SFML/Graphics.hpp>
#include <windows.h>
#include <thread>

Process::Process(sf::RenderWindow *window) {
    _is_menu = true;
    _is_setup = false;
    _is_multiplayer = false;
    _p1_setting_up = true;
    _p2_setting_up = true;

    _favicon.loadFromFile(Constants::favicon_name);
    _window = window;
    _window->setIcon(500, 500, _favicon.getPixelsPtr());

    _menu = new Main_menu(*_window);

    display(); // Actions requiring mutex not started.
    Audio::load();
    Audio::play_theme();
}

Process::~Process() {
    if (_p1_gravity.joinable()){
        _p1_gravity.join();
    }
    if (_p2_gravity.joinable()){
        _p2_gravity.join();
    }
    delete _p1;
    delete _p2;
    delete _menu;
}


void Process::key_pressed(sf::Keyboard::Key keycode) {
    if (_is_setup){
        if (_p1_setting_up){
            _p1_setting_up = _p1->set_keybinds(keycode);

        } else if (!_p1_setting_up && _p2_setting_up){
            _p2_setting_up = _p2->set_keybinds(keycode);

        } else if (!_p1_setting_up && !_p2_setting_up){
            _is_setup = false;
        }
        display(); // Thread not started yet.

    } else if(!_is_menu){
        _mutex.lock();
        _p1->keyboard_event_handler(keycode);
        if (_is_multiplayer){
            _p2->keyboard_event_handler(keycode);
        }
        display();
        _mutex.unlock();
    }
}

void Process::joystick_pressed(unsigned int id, unsigned int button) {
    if (_is_setup){
        if (_p1_setting_up){
            _p1_setting_up = _p1->set_joystick(id);

        } else if(!_p1_setting_up && _p2_setting_up){
            _p2_setting_up = _p2->set_joystick(id);

        } else if (!_p1_setting_up && !_p2_setting_up){
            _is_setup = false;
        }
        display(); // Thread not started yet.

    } else if(!_is_menu){
        _mutex.lock();
        _p1->joystick_button_handler(id, button);
        if (_is_multiplayer){
            _p2->joystick_button_handler(id, button);
        }
        display();
        _mutex.unlock();
    }
}

void Process::joystick_moved(unsigned int id, float x, float y) {
    if (!_is_setup && !_is_menu){
        _mutex.lock();

        _p1->joystick_move_handler(id, x, y);
        if (_is_multiplayer){
            _p2->joystick_move_handler(id, x, y);
        }
        display();
        _mutex.unlock();
    }
}


void Process::closed() {
    _window->close();
}


void Process::key_released(sf::Keyboard::Key keycode) {
    if (keycode == sf::Keyboard::Key::F11){
        if (IsZoomed(_window->getSystemHandle())){
            ShowWindow(_window->getSystemHandle(), SW_SHOWNORMAL);
        } else{
            ShowWindow(_window->getSystemHandle(), SW_MAXIMIZE);
        }
        _mutex.lock();
        display();
        _mutex.unlock();
    }
}

void Process::gained_focus() {
    Audio::play_theme();
}
void Process::lost_focus() {
    Audio::stop_theme();
}

void Process::resized(unsigned int width, unsigned int height) {
    if (_is_menu){
        _menu->resize((float)width, (float)height);
        display(); // Actions requiring mutex not started.
    } else {
        _mutex.lock();
        _p1->resize(width, height);
        if (_is_multiplayer) {
            _p2->resize(width, height);
        }
        display();
        _mutex.unlock();
    }
}

void Process::mouse_pressed(sf::Vector2i mouse_pos) {
    if (_is_menu){
        int click_code = _menu->test_click(mouse_pos);
        if (click_code == 1){
            _is_menu = false;
            _is_setup = true;
            _is_multiplayer = false;
            start_players();
        } else if (click_code == 2){
            _is_menu = false;
            _is_setup = true;
            _is_multiplayer = true;
            start_players();
        }
        _p2_setting_up = _is_multiplayer;
        display(); // Actions requiring mutex not started.
    }
}

void Process::mouse_moved(sf::Vector2i mouse_pos) {
    if (_is_menu){
        _menu->test_hover(mouse_pos);
        display(); // Actions requiring mutex not started.
    }
}


void Process::display() {
    // Currently only called from within mutex protection

    _window->setActive(true);
    _window->clear(sf::Color::White);

    if (_is_menu){
        _window->draw(*_menu);
    } else{
        _window->draw(*_p1);
        if (_is_multiplayer){
            _window->draw(*_p2);
        }
    }

    _window->display();
    _window->setActive(false);
}

//======================================public=======================================
//======================================private======================================

void Process::start_players() {
    _p1 = new Player_instance(_is_multiplayer);
    if (_is_multiplayer){
        _p2 = new Player_instance(true);
    }

    _p1_gravity = std::thread(&Process::gravity_loop1, this);
    if (_is_multiplayer){
        _p2_gravity = std::thread(&Process::gravity_loop2, this);
    }
}


bool Process::game_finished() {
    bool solo_done = !_is_multiplayer && _p1->is_dead();
    bool duo_done = _is_multiplayer && _p1->is_dead() && _p2->is_dead();
    return solo_done || duo_done;
}
void Process::set_winner() {
    if (_is_multiplayer && _p1->is_dead() && _p2->is_dead()){
        if (_p1->get_score() > _p2->get_score()){
            _p1->set_end_state(End_states::Winner);
            _p2->set_end_state(End_states::Loser);
        } else if(_p1->get_score() < _p2->get_score()){
            _p1->set_end_state(End_states::Loser);
            _p2->set_end_state(End_states::Winner);
        } else if(_p1->get_score() == _p2->get_score()){
            _p1->set_end_state(End_states::Tie);
            _p2->set_end_state(End_states::Tie);
        }
    }
}


void Process::gravity_loop1() {
    while (_is_setup){
        if (!_window->isOpen()){
            break;
        }
    }
    while (_window->isOpen()){
        _mutex.lock();
        if (game_finished()){
            set_winner();
            _mutex.unlock();
            break;
        }
        auto delay = _p1->gravity_tick();
        display();
        _mutex.unlock();
        std::this_thread::sleep_for(delay);
    }
}
// Could be one function with a parameter and if-test.
void Process::gravity_loop2() {
    while (_is_setup){
        if (!_window->isOpen()){
            break;
        }
    }
    while (_window->isOpen()){
        _mutex.lock();
        if (game_finished()){
            set_winner();
            _mutex.unlock();
            break;
        }
        auto delay = _p2->gravity_tick();
        display();
        _mutex.unlock();
        std::this_thread::sleep_for(delay);
    }
}