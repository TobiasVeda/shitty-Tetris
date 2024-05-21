#include "Main_menu.h"
#include "Process.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>

//TODO: Fix include order, add const when what the function recieves shouldnt be edited
//TODO: Error handling when not finding texture(apply error texture), UI magic numbers
//TODO: mvc, fix collision, static texture?, Blockbag cant be static


int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    bool window_open = true;
    bool is_menu = true;
    bool is_setup = true;
    bool is_multiplayer = false;
    window.setActive(false);

    auto menu = new Main_menu(window);
    auto p1 = new Process;
    auto p2 = new Process;

//    Process p2(2);

//empty construct

    std::thread p1_grvty(&Process::gravity_loop, p1, std::ref(window_open));
    std::thread p2_grvty(&Process::gravity_loop, p2, std::ref(window_open));

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_open = false;
                window.close();
            }



            if (is_menu){
                if (event.type == sf::Event::MouseButtonPressed){
                    int click_code = menu->test_click(sf::Mouse::getPosition(window));
                    if (click_code == 1){
                        is_menu = false;
                        is_multiplayer = false;
                    } else if (click_code == 2){
                        is_menu = false;
                        is_multiplayer = true;
                    }
                } else{
                    menu->test_hover(sf::Mouse::getPosition(window));
                }
            }

            if (!is_menu){

                static bool first = true;
                if (first){
                    p1->init(is_multiplayer);
                    if (is_multiplayer){
                        p2->init(is_multiplayer);
                    }
                    first = false;
                }


                if (event.type == sf::Event::KeyPressed){
                    if (is_setup){
                        if (p1->set_keybinds(event.key.code)){
                        } else if(is_multiplayer && p2->set_keybinds(event.key.code)){
                        } else{
                            is_setup = false;
                        }

                    } else{
                        p1->event_handler(event.key.code);
                        if (is_multiplayer){
                            p2->event_handler(event.key.code);
                        }
                    }
            }


            }
        }



        window.clear(sf::Color::White);
        if (is_menu){
            window.draw(*menu);
        } else{
            p1->draw(window);
            if (is_multiplayer){
                p2->draw(window);
            }
        }

        window.display();
    }

    p1_grvty.join();
    p2_grvty.join();

}

