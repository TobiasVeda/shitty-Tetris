//
// Created by tobia on 26.04.2024.
//

#ifndef SHITTY_TETRIS_GAME_H
#define SHITTY_TETRIS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include <map>

class Game {
private:
    static inline sf::RenderWindow _window;
    static inline sf::View _view;
    static inline sf::RectangleShape _bound_L;
    static inline sf::RectangleShape _bound_R;
    static inline sf::RectangleShape _bound_D;
    static inline std::map<std::string, sf::RectangleShape> _bounds;

    static inline std::vector<std::list<sf::RectangleShape>> _block_stack;

    static void set_bounds();
    static void move_line_down(std::vector<int>&);
public:
    static void create_window();
    static sf::RenderWindow* get_window();
    static sf::View* get_view();
    static sf::RectangleShape* get_bounds(std::string);

    static void add_to_collection(std::list<sf::RectangleShape>*);
    static const std::vector<std::list<sf::RectangleShape>>* get_stack();
    static void try_lineclear();
};


#endif //SHITTY_TETRIS_GAME_H
