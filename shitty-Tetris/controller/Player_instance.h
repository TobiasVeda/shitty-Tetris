//
// Created by tobia on 09.05.2024.
//

#ifndef SHITTY_TETRIS_PLAYER_INSTANCE_H
#define SHITTY_TETRIS_PLAYER_INSTANCE_H

#include "../model/Game.h"
#include "../view/Tilemap.h"
#include "../view/UI.h"
#include "../model/Keybinds.h"
#include <SFML/Graphics.hpp>


class Player_instance : public sf::Drawable{
private:

    int _player;
    Game *_game;
    Keybinds *_keybinds;
    Tilemap *_tilemap;
    UI *_ui;

    int _keybind_loop;

    bool _joystick_ready = true;
    bool _joystick_assigned = false;

    bool _is_dead;

    void draw(sf::RenderTarget&, sf::RenderStates) const override;

public:
    explicit Player_instance(bool);
    ~Player_instance();

    bool set_keybinds(sf::Keyboard::Key);
    bool set_joystick(unsigned int);

    void keyboard_event_handler(sf::Keyboard::Key);
    void joystick_button_handler(unsigned int, unsigned int);
    void joystick_move_handler(unsigned int, float, float);

    void set_end_state(Constants::End_states);
    [[nodiscard]] bool is_dead() const;
    [[nodiscard]] unsigned int get_score() const;

    std::chrono::milliseconds gravity_tick();

    void resize(unsigned int, unsigned int);

};


#endif //SHITTY_TETRIS_PLAYER_INSTANCE_H
