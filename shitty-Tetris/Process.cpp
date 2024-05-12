//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "pieces/Base_shape.h"
#include "Block_bag.h"
#include "Game.h"
#include "Player.h"

void Process::game_loop(int player) {

    static bool key_hold = false;

    Game game(player);//move out when thread

    Player p(player);

    Base_shape a;

    a = Block_bag::get_new_block();

    Tilemap map;
    if (!map.load()) {
//        return -1;
    }

//    Game::get_window()->setActive(true);
    while (Game::get_window()->isOpen()){

        static int long_delay = 0;

        long_delay++;

        p.keyboard_controller(&a, key_hold);

        if (long_delay == Constants::long_game_tick){
            a.try_placing(); // might need to refresh delay on move
            a.gravity();
            game.try_lineclear();
            if (a.is_placed()){
                game.add_to_collection(a.get_block_list());
                a = Block_bag::get_new_block(&game);
            }
            long_delay = 0;
        }


        sf::Event event{};
        while (Game::get_window()->pollEvent(event)){
            if(event.type == sf::Event::Closed) {
                Game::get_window()->close();
            }
            if (event.type == sf::Event::KeyPressed){
                key_hold = true;
            }
            if (event.type == sf::Event::KeyReleased){
                key_hold = false;
            }

        }


        Game::get_window()->clear(sf::Color::White);
        Game::get_window()->draw(map);
        Game::get_window()->draw(a);
        Game::get_window()->draw(game);


        Game::get_window()->display();

        Constants::wait_game_tick();
    }

}