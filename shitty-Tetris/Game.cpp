//
// Created by tobia on 26.04.2024.
//

#include "Game.h"
#include <string>
#include <map>
#include "Constants.h"
#include <algorithm>
Game::Game(int player) {
    _window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    if (player == 0){
        _view.setCenter(sf::Vector2f(200,360));
        _view.setSize(sf::Vector2f(400, 720));
        _view.setViewport(sf::FloatRect(0, 0, 0.21, 0.67));
        _window.setView(_view);
    }

    set_bounds();
}

void Game::set_bounds() {
    auto size_L_R = sf::Vector2f(1, _view.getSize().y + 2);
    auto size_B = sf::Vector2f(_view.getSize().x + 2, 1);

    _bound_L.setSize(size_L_R);
    _bound_R.setSize(size_L_R);
    _bound_D.setSize(size_B);

    _bound_L.setPosition(
            (_view.getCenter().x - (_view.getSize().x /2) - _bound_L.getSize().x),
            (_view.getCenter().y - (_view.getSize().y /2))
            );
    _bound_R.setPosition(
            (_view.getCenter().x + (_view.getSize().x /2)),
            (_view.getCenter().y - (_view.getSize().y /2))
            );
    _bound_D.setPosition(
            (_view.getCenter().x - (_view.getSize().x /2) -1),
            (_view.getCenter().y + (_view.getSize().y /2))
            );

    _bounds["right"] = _bound_R;
    _bounds["left"] = _bound_L;
    _bounds["down"] = _bound_D;
}

void Game::move_line_down(std::vector<int> &coord_line_cleared) {
    sf::Vector2f block_check;
    const auto bottom_left = sf::Vector2f(
            _view.getCenter().x - (_view.getSize().x /2) +1,
            _view.getCenter().y + (_view.getSize().y /2) -1
    ); // +-1 because contains does not check edges of shape

    for (int z = 0; z < coord_line_cleared.size(); ++z) {

        for (int y = 0; y < Constants::tile_count_y; ++y) {

            for (int x = 0; x < Constants::tile_count_x; ++x) {
                block_check = sf::Vector2f(
                        bottom_left.x + (x * Constants::tilesize.x),
                        bottom_left.y - (y * Constants::tilesize.y) - (coord_line_cleared[z] * Constants::tilesize.y)
                );


                for (auto& i : _block_stack) {
                    for (auto j = i.begin(); j != i.end(); ++j) {

                        if (j->getGlobalBounds().contains(block_check)){
                            j->move(0, Constants::tilesize.y);
                            goto BREAK;
                        }
                    }
                }

                BREAK:
                int i_just_want_to_be_able_to_skip_two_loops_with_one_break_but_need_code_after_label_to_compile = 0;

            }
        }
    }

}




sf::RenderWindow* Game::get_window() {
    return &_window;
}

sf::View* Game::get_view() {
    return &_view;
}

sf::RectangleShape* Game::get_bounds(std::string dir){
    return &_bounds[dir];
}

void Game::add_to_collection(std::list<sf::RectangleShape> *block) {
    _block_stack.emplace_back(*block);
}

const std::vector<std::list<sf::RectangleShape>>* Game::get_stack(){
    return &_block_stack;
}

bool Game::is_filled(sf::Vector2f &check_coord) {

    for (auto& i : _block_stack) {
        for (auto j = i.begin(); j != i.end(); ++j) {

            if (j->getGlobalBounds().contains(check_coord)){
                return true;
            }

        }
    }
    return false;
}

void Game::clear_row(float y) {
    sf::Vector2f check_coord;
    const auto bottom_left = sf::Vector2f(
            _view.getCenter().x - (_view.getSize().x /2) +1,
            _view.getCenter().y + (_view.getSize().y /2) -1
    ); // +-1 because "contains" does not check edges of shape

    for (int x = 0; x < Constants::tile_count_x; ++x) {
        check_coord = sf::Vector2f(
                bottom_left.x + (float)(x * Constants::tilesize.x),
                bottom_left.y - (y * (float)Constants::tilesize.y)
        );

        for (auto& i : _block_stack) {
            for (auto j = i.begin(); j != i.end(); ++j) {

                if (j->getGlobalBounds().contains(check_coord)){
                    i.erase(j);
                    goto BREAK;
                }

            }
        }
        BREAK:
        bool need_code_below_label;
    }

}

void Game::try_lineclear() {
    sf::Vector2f check_coord;
    std::vector<int> coord_line_cleared;
    const auto bottom_left = sf::Vector2f(
            _view.getCenter().x - (_view.getSize().x /2) +1,
            _view.getCenter().y + (_view.getSize().y /2) -1
            ); // +-1 because "contains" does not check edges of shape


    for (int y = 0; y < Constants::tile_count_y; ++y) {
        int fill_count = 0;

        for (int x = 0; x < Constants::tile_count_x; ++x) {
            check_coord = sf::Vector2f(
                    bottom_left.x + (float)(x * Constants::tilesize.x),
                    bottom_left.y - (float)(y * Constants::tilesize.y)
            );

            if (!is_filled(check_coord)){
                break;
            } else{
                fill_count++;
            }
            if (fill_count == Constants::tile_count_x){
                float line_cleared_coord = (Constants::tile_count_y) - ((check_coord.y +1 ) / (float)Constants::tilesize.y);
                coord_line_cleared.emplace_back(line_cleared_coord);

                clear_row((float)y);
            }

        }


    }
    
    move_line_down(coord_line_cleared);
}
