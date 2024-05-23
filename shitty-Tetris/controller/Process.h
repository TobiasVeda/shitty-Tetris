//
// Created by tobia on 22.05.2024.
//

#ifndef SHITTY_TETRIS_PROCESS_H
#define SHITTY_TETRIS_PROCESS_H

#include "Player_instance.h"
#include "../view/Main_menu.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>


class Process {
private:

    std::mutex _mutex;

    bool _is_menu;
    bool _is_setup;
    bool _is_multiplayer;
    bool _p1_setting_up;
    bool _p2_setting_up;

    sf::RenderWindow *_window;
    sf::Image _favicon;

    Main_menu *_menu;

    Player_instance *_p1;
    Player_instance *_p2;

    void start_players();

    bool game_finished();
    void set_winner();

    void gravity_loop1(); // mutex
    void gravity_loop2(); // mutex

    void display();

public:
    explicit Process(sf::RenderWindow*);
    ~Process();

    void key_pressed(sf::Keyboard::Key); // mutex
    void joystick_pressed(unsigned int, unsigned int); // mutex
    void joystick_moved(unsigned int, float, float); // mutex

    void closed();
    void key_released(sf::Keyboard::Key);
    void gained_focus();
    void lost_focus();
    void resized(unsigned int, unsigned int);
    void mouse_pressed(sf::Vector2i);
    void mouse_moved(sf::Vector2i);
};


#endif //SHITTY_TETRIS_PROCESS_H
