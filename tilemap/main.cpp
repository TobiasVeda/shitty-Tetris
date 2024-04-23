#include <SFML/Graphics.hpp>
#include "Tilemap.h"
#include <list>
#include <thread>
#include <iostream>
#include "Constants.h"
#include "T_block.h"
#include <chrono>

int main()
{


//AND SET UP GIT!!!!!!!!!


    // create the window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Tilemap");
    sf::View view;
    view.setCenter(sf::Vector2f(200,360));
    view.setSize(sf::Vector2f(400, 720));
    view.setViewport(sf::FloatRect(0, 0, 0.21, 0.67));
    window.setView(view);
    T_block a;

    sf::RectangleShape line(sf::Vector2f( 80, 320));
    line.setFillColor(sf::Color::Blue);
    line.setPosition(sf::Vector2f(80, 1120));

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
        window.draw(line);
        window.draw(a);

        window.display();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}

