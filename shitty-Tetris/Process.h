//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_PROCESS_H
#define SHITTY_TETRIS_PROCESS_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Tilemap.h"
#include "UI.h"
#include "Keybinds.h"

class Process {
protected:
    Game _game;
    Keybinds _keybinds;
    Tilemap _tilemap;
    UI _ui;

    bool _keep_alive;

    int _long_delay;

public:
    Process(sf::RenderWindow&, int);
    void game_loop();
    void draw(sf::RenderWindow&, int);

};


#endif //SHITTY_TETRIS_PROCESS_H
