//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Game.h"
#include "Keybinds.h"
#include "UI.h"
#include <thread>

Process::Process(int player) {
    _player = player;
    _is_setup = true;
    _keybind_loop = 0;

    _game = new Game(_player);
    _keybinds = new Keybinds;
    _ui = new UI();
    _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Setup);
    _tilemap = new Tilemap();
}
Process::~Process(){
    delete _game;

    delete _tilemap;
    delete _ui;
}

void Process::gravity_loop(bool &window_open) {
    while (_is_setup){};

    while (window_open) {
        _process_mutex.lock();

        _game->do_gametick_action();
        _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);

        _process_mutex.unlock();

        auto delay = std::chrono::milliseconds((long long)_game->get_gravity_delay_ms());
        std::this_thread::sleep_for(delay);
    }
}

void Process::event_handler(sf::Keyboard::Key key){
    _process_mutex.lock();

    _game->do_action(_keybinds->translate_key(key));
    _ui->update(_game->get_held_type(), _game->get_scoreboard(), Constants::Run);

    _process_mutex.unlock();
}

bool Process::set_keybinds(sf::Keyboard::Key keycode) {

    if (keycode == sf::Keyboard::Key::Enter){
        _keybinds->assign_default(_player);
        _keybind_loop = 7;
        _is_setup = false;
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
                _is_setup = false;
                return false;
        }
    } else{
        return false;
    }
}

void Process::draw(sf::RenderWindow &window) {
    // sf::Drawable not used so that mutex can be locked/unlocked

    _process_mutex.lock();

    window.setView(_game->get_view());

    window.draw(*_tilemap);
    window.draw(*_game);
    window.draw(*_ui);

    _process_mutex.unlock();
}