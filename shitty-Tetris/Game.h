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
    sf::View _view;
    sf::RectangleShape _bound_L;
    sf::RectangleShape _bound_R;
    sf::RectangleShape _bound_D;
    std::map<std::string, sf::RectangleShape> _bounds;

    std::vector<std::list<sf::RectangleShape>> _block_stack;

    void set_bounds();
    void move_line_down(std::vector<int>&);
    void clear_row(float);
    bool is_filled(sf::Vector2f&);
public:
    Game(int);
    static sf::RenderWindow* get_window();
    sf::View* get_view();
    sf::RectangleShape* get_bounds(std::string);

    void add_to_collection(std::list<sf::RectangleShape>*);
    const std::vector<std::list<sf::RectangleShape>>* get_stack();
    void try_lineclear();
};


#endif //SHITTY_TETRIS_GAME_H
