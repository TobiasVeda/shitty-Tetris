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

    bool _is_dead;

public:
    Process() = default;
    ~Process();
    void init(bool multiplayer = false);
    void event_handler(sf::Keyboard::Key);
    void gravity_loop(bool&);
    void draw(sf::RenderWindow&);
    bool set_keybinds(sf::Keyboard::Key);

};


#endif //SHITTY_TETRIS_PROCESS_H
