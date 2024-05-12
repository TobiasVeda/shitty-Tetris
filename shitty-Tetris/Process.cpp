//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Game.h"
#include "Player.h"

void Process::game_loop(int player) {

    bool key_hold = false;

    Game game(player);

    Player p(player);


    Tilemap map;
    try {
        if (!map.load()) {
            throw -1;
        }
    } catch (int a){

    }




//    Game::get_window()->setActive(true);
    while (Game::get_window().isOpen()){

        static int long_delay = 0;

        long_delay++;

        game.do_action(p.keyboard_controller(key_hold));


        if (long_delay == Constants::long_game_tick){
            game.do_gametick_action();
            long_delay = 0;
        }


        sf::Event event{};
        while (Game::get_window().pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                Game::get_window().close();
            }
            if (event.type == sf::Event::KeyPressed){
                key_hold = true;
            }
            if (event.type == sf::Event::KeyReleased){
                key_hold = false;
            }

        }


        Game::get_window().clear(sf::Color::White);

        Game::get_window().draw(map);
        Game::get_window().draw(game);

        Game::get_window().display();

        Constants::wait_game_tick();
    }

}