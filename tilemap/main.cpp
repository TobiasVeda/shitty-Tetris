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

    Base_shape a = Block_bag::get_new_block();


    Tilemap map;
    if (!map.load())
        return -1;




    while (window.isOpen()){
        sf::Event event{};
        while (window.pollEvent(event)){
            if(event.type == sf::Event::Closed)
                window.close();
        }
        a.move(&view);

        window.clear(sf::Color::White);


        window.draw(map);


        window.draw(a);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

