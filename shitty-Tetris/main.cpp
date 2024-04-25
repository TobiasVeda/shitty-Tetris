#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include <list>
#include <thread>
#include <iostream>
#include "Constants.h"
#include "pieces/T_block.h"
#include <chrono>
#include "pieces/O_block.h"
#include "pieces/Base_shape.h"
#include "Block_bag.h"
#include "Block_stack.h"

//TODO: Fix include order, put defenition of keyup,down,right in class, add const when what the function recieves shouldnt be edited

//TODO: Make a block able to be placed, then add to collection, add collision with collection
//TODO: Line clear

//when placed, add to collection. when cleared remove from collection, when move check intersect with collection

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "shitty Tetris");
    sf::View view;
    view.setCenter(sf::Vector2f(200,360));
    view.setSize(sf::Vector2f(400, 720));
    view.setViewport(sf::FloatRect(0, 0, 0.21, 0.67));
    window.setView(view);

    Base_shape a;

    Block_bag::get_new_block(&a);


    Tilemap map;
    if (!map.load())
        return -1;
    

    while (window.isOpen()){
        static int delay = 0;
        delay++;
        if (delay == Constants::long_game_tick){
            a.try_placing(&view);
            a.gravity(&view);
            //a.lineclear osv
            delay = 0;
        }

        a.move(&view);

        if (a.is_placed()){
            Block_stack::add_to_collection(&a);
            Block_bag::get_new_block(&a);
        }


        sf::Event event{};
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }


        window.clear(sf::Color::White);

        window.draw(map);
        window.draw(a);
        for (auto& i : *Block_stack::get_stack()) {
            window.draw(i);
        }

        window.display();

        Constants::wait_game_tick();
    }

    return 0;
}

