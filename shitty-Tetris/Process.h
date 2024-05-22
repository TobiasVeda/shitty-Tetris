//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_PROCESS_H
#define SHITTY_TETRIS_PROCESS_H

#include "Game.h"
#include "Tilemap.h"
#include "UI.h"
#include "Keybinds.h"
#include <SFML/Graphics.hpp>
#include <mutex>

class Process{
protected:
    std::mutex _process_mutex;

    int _player;

    Game *_game;
    Keybinds *_keybinds;
    Tilemap *_tilemap;
    UI *_ui;

    bool _is_setup;

    int _keybind_loop;

    bool _joystick_ready = true;
    bool _joystick_assigned = false;

    bool _is_dead;

public:
    Process();
    ~Process();
    void init(bool multiplayer = false);
    void run();

    bool set_keybinds(sf::Keyboard::Key);
    bool set_joystick(unsigned int);

    void keyboard_event_handler(sf::Keyboard::Key);
    void joystick_button_handler(unsigned int, unsigned int);
    void joystick_move_handler(unsigned int, float, float);

    void gravity_loop(bool&);

    void resize(float, float);
    void display(sf::RenderWindow&);
};


#endif //SHITTY_TETRIS_PROCESS_H
