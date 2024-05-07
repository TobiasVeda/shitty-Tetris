#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include "Constants.h"
#include "pieces/Base_shape.h"
#include "Block_bag.h"
#include "Game.h"

//TODO: Fix include order, put defenition of keyup,down,right in class, add const when what the function recieves shouldnt be edited
//put view in class to prevent passing?? Moved, but not sure if all includes fixed
//Deconstruct cleared blocks??
//all things relative to view will break when view is expanded to include "next blocks" and "hold".
//      can probably still use center, but must expand from center with tilesize * tilecount_x/y
// make move diagonal possible
//TODO: Error handling when not finding texture


int main(){

    Game::create_window();

    Base_shape a;

    Block_bag::get_new_block(&a);


    Tilemap map;
    if (!map.load())
        return -1;


    while (Game::get_window()->isOpen()){
        static int long_delay = 0;
        static int short_delay = 0;
        long_delay++;
        short_delay++;

        if (long_delay == Constants::long_game_tick){
            a.try_placing(Game::get_view()); // might need to refresh delay on move
            a.gravity();
            Game::try_lineclear();
            long_delay = 0;
        }
        if (short_delay == Constants::short_game_tick){
            a.move(Game::get_view());
            a.rotate_block();
            short_delay = 0;
        }



        if (a.is_placed()){
            Game::add_to_collection(a.get_block_list());
            Block_bag::get_new_block(&a);
        }


        sf::Event event{};
        while (Game::get_window()->pollEvent(event)){
            if(event.type == sf::Event::Closed)
                Game::get_window()->close();
        }


        Game::get_window()->clear(sf::Color::White);
            Game::get_window()->draw(map);
            Game::get_window()->draw(a);
            for (auto& stack_block : *Game::get_stack()) {
                for (auto& stack_rectangle : stack_block) {
                    Game::get_window()->draw(stack_rectangle);
                }

            }
            Game::get_window()->display();

        Constants::wait_game_tick();
    }

    return 0;
}

