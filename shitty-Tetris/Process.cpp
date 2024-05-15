//
// Created by tobia on 09.05.2024.
//

#include "Process.h"
#include "Tilemap.h"
#include "Constants.h"
#include "Game.h"
#include "Keybinds.h"
#include "UI.h"

void Process::game_loop(sf::RenderWindow &window, int player) {

    window.setActive(true);

    bool key_hold = false;

    static Game game(window, player);

    static Keybinds keybinds(player);

    static UI ui;

    static Tilemap map;
    try {
        if (!map.load()) {
            throw -1;
        }
    } catch (int a){

    }



//    while (window.isOpen()){


        static int long_delay = 0;

        long_delay++;

        game.do_action(keybinds);
        ui.update(game.get_held_type(), game.get_scoreboard());


        if (long_delay == Constants::long_game_tick){
            game.do_gametick_action();
            long_delay = 0;
        }

        window.clear(sf::Color::White);

        window.draw(map);
        window.draw(game);
        window.draw(ui);
        window.display();


//        Constants::wait_game_tick();
//
//    }

}