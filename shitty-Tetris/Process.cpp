//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Game.h"
#include "Keybinds.h"
#include "UI.h"

#include <iostream>

//Process::Process(RenderWindow &window)
//{
//    this.window = window;
//
//    // Make new thread to run gravity
//}
//
//void Process::Close()
//{
//    window.close();
//}
//
//void Process::KeyPressed(string key)
//{
//    // Do action based on key stroke
//}

Process::Process(sf::RenderWindow &window, int player) {
    _game = Game(window, player);
    _keybinds = Keybinds(player);
    _ui = UI();
    _ui.load();
    _tilemap = Tilemap();
    _tilemap.load();
    _long_delay = 0;
}



void Process::game_loop() {


    bool key_hold = false;

//    while (window.isOpen()){

        _long_delay++;

        _game.do_action(_keybinds);
        _ui.update(_game.get_held_type(), _game.get_scoreboard());


        if (_long_delay == Constants::long_game_tick){
            _game.do_gametick_action();
            _long_delay = 0;
        }




//        Constants::wait_game_tick();
//
//    }

}

void Process::draw(sf::RenderWindow &window, int player) {
    sf::View _view;
    _view.setSize(sf::Vector2f(600, 720));
    _view.setCenter(sf::Vector2f(300,360));
    if (player == 0){
        _view.setViewport(sf::FloatRect(0.356f, 0.1, 0.36f, 0.75));
    } else if (player == 1){
        _view.setViewport(sf::FloatRect(0.13f, 0.1, 0.36f, 0.75));
    } else if (player == 2){
        _view.setViewport(sf::FloatRect(0.63f, 0.1, 0.36f, 0.75));
    }

    window.setView(_view);


    window.draw(_tilemap);
    window.draw(_game);
    window.draw(_ui);
}