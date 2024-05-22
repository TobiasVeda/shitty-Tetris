#include "Main_menu.h"
#include "Process.h"
#include "Audio.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <iostream>
#include <windows.h>

//TODO: add const when what the function recieves shouldnt be edited
//TODO: Error handling when not finding texture(apply error texture), UI magic numbers
//TODO: mvc, fix collision, Blockbag cant be static
//TODO: Private/Protected

int main(){

    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    sf::Image favicon;
    favicon.loadFromFile(Constants::favicon_name);
    window.setIcon(500, 500, favicon.getPixelsPtr());
    bool window_open = true;
    bool is_menu = true;
    bool is_setup = true;
    bool is_multiplayer = false;
    bool p1_setting_up = true;
    bool p2_setting_up = true;
    window.setActive(false);
    Audio::load();
    Audio::play_theme();

    auto menu = new Main_menu(window);
    auto p1 = new Process;
    auto p2 = new Process;

    std::thread p1_grvty(&Process::gravity_loop, p1, std::ref(window_open));
    std::thread p2_grvty(&Process::gravity_loop, p2, std::ref(window_open));

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window_open = false;
                window.close();
            }
            if (event.type == sf::Event::KeyReleased){
                if (event.key.code == sf::Keyboard::Key::F11){
                    if (IsZoomed(window.getSystemHandle())){
                        ShowWindow(window.getSystemHandle(), SW_SHOWNORMAL);
                    } else{
                        ShowWindow(window.getSystemHandle(), SW_MAXIMIZE);
                    }
                }
            }
            if (event.type == sf::Event::LostFocus){
                Audio::stop_theme();
            } else if (event.type == sf::Event::GainedFocus){
                Audio::play_theme();
            }
            if (event.type == sf::Event::Resized){
                p1->resize((float)event.size.width, (float)event.size.height);
                if (is_multiplayer){
                    p2->resize((float)event.size.width, (float)event.size.height);
                }
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
                    p2_setting_up = is_multiplayer;
                } else{
                    menu->test_hover(sf::Mouse::getPosition(window));
                }
            }

            if(!is_menu){ // Breaks when else instead of if

                static bool first = true;
                if (first){
                    p1->init(is_multiplayer);
                    if (is_multiplayer){
                        p2->init(is_multiplayer);
                    }
                    first = false;
                }

                if (is_setup && event.type == sf::Event::JoystickButtonPressed){
                    if (p1_setting_up){
                        p1_setting_up = p1->set_joystick(event.joystickConnect.joystickId);
                    }
                    if(!p1_setting_up && p2_setting_up){
                        p2_setting_up = p2->set_joystick(event.joystickConnect.joystickId);
                    }


                } else if (!is_setup && event.type == sf::Event::JoystickButtonPressed){
                    p1->joystick_button_handler(event.joystickButton.joystickId, event.joystickButton.button);
                    if (is_multiplayer){
                        p2->joystick_button_handler(event.joystickButton.joystickId, event.joystickButton.button);
                    }
                }
                if (!is_setup && event.type == sf::Event::JoystickMoved){
                    unsigned int id = event.joystickButton.joystickId;
                    float x = sf::Joystick::getAxisPosition(id, sf::Joystick::X);
                    float y = sf::Joystick::getAxisPosition(id, sf::Joystick::Y);

                    p1->joystick_move_handler(id, x, y);
                    if (is_multiplayer){
                        p2->joystick_move_handler(id, x, y);
                    }
                }

                if (is_setup && event.type == sf::Event::KeyPressed){
                    if (p1_setting_up){
                        p1_setting_up = p1->set_keybinds(event.key.code);
                    }

                    if (!p1_setting_up && p2_setting_up){
                        p2_setting_up = p2->set_keybinds(event.key.code);
                    }

                } else if (!is_setup && event.type == sf::Event::KeyPressed){
                    p1->keyboard_event_handler(event.key.code);
                    if (is_multiplayer){
                        p2->keyboard_event_handler(event.key.code);
                    }
                }

                if (!p1_setting_up && !p2_setting_up){
                    is_setup = false;
                    p1->run();
                    if (is_multiplayer){
                        p2->run();
                    }
                }
            }
        } // end of eventloop



        window.clear(sf::Color::White);
        if (is_menu){
            window.draw(*menu);
        } else{
            p1->display(window);
            if (is_multiplayer){
                p2->display(window);
            }
        }

        window.display();
//        std::this_thread::sleep_for (std::chrono::milliseconds(10));
    }

    p1_grvty.join();
    p2_grvty.join();
    delete p1;
    delete p2;
}

