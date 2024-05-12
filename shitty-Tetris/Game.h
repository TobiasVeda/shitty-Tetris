//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <map>
#include <mutex>
#include "pieces/Base_shape.h"

class Game : public sf::Drawable{
protected:
    static inline sf::RenderWindow _window;
    Base_shape _player_controlled_block;
    sf::View _view;
    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;
    std::map<std::string, sf::RectangleShape> _bounds;

    std::vector<std::list<sf::RectangleShape>> _block_stack;
//    does not need list

    void set_bounds();
    void move_line_down(std::vector<int>&);
    void clear_row(float);
    bool is_filled(sf::Vector2f&);

    void move_player(int);
    void rotate_player();
    void drop_player();

public:
//    static void create_window();
    Game(int);
    static sf::RenderWindow* get_window();
    sf::View* get_view();
    sf::RectangleShape* get_bounds(std::string);

    void add_to_collection(std::list<sf::RectangleShape>*);
    const std::vector<std::list<sf::RectangleShape>>* get_stack();
    void try_lineclear();
    void do_gametick_action();
    void do_action(int);

    void draw(sf::RenderTarget&, sf::RenderStates) const override;
};


#endif //SHITTY_TETRIS_GAME_H
