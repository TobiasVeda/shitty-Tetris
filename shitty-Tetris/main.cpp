#include <SFML/Graphics.hpp>
#include "Process.h"
#include <thread>
#include "Constants.h"
#include <iostream>
#include "Main_menu.h"

//TODO: Fix include order, add const when what the function recieves shouldnt be edited
//TODO: Error handling when not finding texture(apply error texture), UI magic numbers
//TODO: mvc, main menu, death menu, fix collision, speedup, static texture?


int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    bool window_open = true;
    bool is_startup = true;
    bool is_setup = true;
    window.setActive(false);

    auto menu = new Main_menu(window);
    auto p1 = new Process;

//    Process p2(2);

//empty construct

    std::thread p1_grvty(&Process::gravity_loop, p1, std::ref(window_open));
//    std::thread p2_grvty(&Process::gravity_loop, &p2, std::ref(window_open));

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_open = false;
                window.close();
            }



            if (is_startup){
                if (event.type == sf::Event::MouseButtonPressed){
                    is_startup = !menu->test_click(sf::Mouse::getPosition(window));

                } else{
                    menu->test_hover(sf::Mouse::getPosition(window));
                }
            }

            if (!is_startup){

                static bool first = true;
                if (first){
                    p1->init();
                    first = false;
                }


                if (event.type == sf::Event::KeyPressed){
                    if (is_setup){
//                        if 2player
                        if (p1->set_keybinds(event.key.code)){
//                        } else if(p2.set_keybinds(event.key.code)){
                        } else{
                            is_setup = false;
                        }

                    } else{
                        p1->event_handler(event.key.code);
                        //if 2player
//                    p2.event_handler(event.key.code);
                    }
            }


            }
        }



        window.clear(sf::Color::White);
        if (is_startup){
            window.draw(*menu);
        } else{
            p1->draw(window);
            //if 2player
//        p2.draw(window);
        }

        window.display();
    }

//    p1_grvty.join();
//    p2_grvty.join();

}

