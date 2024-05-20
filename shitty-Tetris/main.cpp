#include <SFML/Graphics.hpp>
#include "Process.h"
#include <thread>
#include "Constants.h"
#include <iostream>

//TODO: Fix include order, add const when what the function recieves shouldnt be edited
//TODO: Error handling when not finding texture(apply error texture), UI magic numbers
//TODO: mvc, main menu, death menu, fix collision, speedup, static texture?


int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    bool window_open = true;
    bool is_setup = true;
    window.setActive(false);

    Process p1(0);
//    Process p2(2);

    std::thread p1_grvty(&Process::gravity_loop, &p1, std::ref(window_open));
//    std::thread p2_grvty(&Process::gravity_loop, &p2, std::ref(window_open));

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_open = false;
                window.close();
            }
            if (event.type == sf::Event::KeyPressed){
                if (is_setup){
                    if (p1.set_keybinds(event.key.code)){
//                    } else if(p2.set_keybinds(event.key.code)){
                    } else{
                        is_setup = false;
                    }

                } else{
                    p1.event_handler(event.key.code);
//                    p2.event_handler(event.key.code);
                }



            }
            if (event.type == sf::Event::JoystickButtonPressed){
                auto g = event.joystickButton.joystickId;
                int o= 1;
            }
        }



        window.clear(sf::Color::White);
        p1.draw(window);
//        p2.draw(window);
        window.display();
//        Constants::wait_event_tick();
    }

    p1_grvty.join();
//    p2_grvty.join();

}

