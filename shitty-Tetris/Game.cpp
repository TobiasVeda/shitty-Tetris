//
// Created by tobia on 26.04.2024.
//

#include "Game.h"
#include <string>
#include <map>
#include "Constants.h"
#include "Block_bag.h"
//void Game::create_window() {
//    _window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
//}

Game::Game(int player) {
    _window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    _view.setSize(sf::Vector2f(400, 720));
    _view.setCenter(sf::Vector2f(200,360));
    if (player == 0){
        _view.setViewport(sf::FloatRect(0.356f, 0.1, 0.24f, 0.75));
    } else if (player == 1){
        _view.setViewport(sf::FloatRect(0.13f, 0.1, 0.24f, 0.75));
    } else if (player == 2){
        _view.setViewport(sf::FloatRect(0.63f, 0.1, 0.24f, 0.75));
    }
    _window.setView(_view);

    _player_controlled_block = Block_bag::get_new_block();

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
}




void Game::add_player_to_collection() {
    // Does not check for duplicates. Should be sure that rectangles added does
    // not overlap with already existing rectangles.
    // Should add a copy to _block_stack
    for (const auto i : _player_controlled_block.get_rectangle_list()) {
        _block_stack.emplace_back(i);
    }
}











void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(_player_controlled_block, states);

    for (auto& i : _block_stack) {
            target.draw(i, states);
    }

}

void Game::do_gametick_action() {
    try_placing_player();
    gravity();
    try_lineclear();
    if (_player_controlled_block.is_placed()){
        add_player_to_collection();
        _player_controlled_block = Block_bag::get_new_block();
    }
}

void Game::move_player(Constants::Directions direction){
    // To be able to move horizontally and vertically at the same time,
    // all cases of "move" must be possible to execute from one run
    bool next_pos_valid_down = player_clear_to_move_right();
    bool next_pos_valid_right = player_clear_to_move_right();
    bool next_pos_valid_left = player_clear_to_move_left();

    if (direction == Constants::Down && next_pos_valid_down){
        auto down = sf::Vector2f(0, (float)Constants::tilesize.y);
        _player_controlled_block.move(down);
    }
    if (direction == Constants::Right && next_pos_valid_right){
        auto right = sf::Vector2f( (float)Constants::tilesize.y, 0);
        _player_controlled_block.move(right);
    }
    if (direction == Constants::Left && next_pos_valid_left){
        auto left = sf::Vector2f(-1 * (float)Constants::tilesize.y, 0);
        _player_controlled_block.move(left);
    }

}

bool Game::player_clear_to_move_down(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto down = sf::Vector2f(0, (float)Constants::tilesize.y);
    _player_controlled_block.move(down);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        auto up = sf::Vector2f(-1 * down.x, -1 * down.y);
        _player_controlled_block.move(up);
    } else if(!auto_commit){
        auto up = sf::Vector2f(-1 * down.x, -1 * down.y);
        _player_controlled_block.move(up);
    }
}
bool Game::player_clear_to_move_right(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto right = sf::Vector2f((float)Constants::tilesize.x, 0);
    _player_controlled_block.move(right);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        auto left = sf::Vector2f(-1 * right.x, -1 * right.y);
        _player_controlled_block.move(left);
    } else if(!auto_commit){
        auto left = sf::Vector2f(-1 * right.x, -1 * right.y);
        _player_controlled_block.move(left);
    }
}
bool Game::player_clear_to_move_left(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto left = sf::Vector2f(-1 * (float)Constants::tilesize.x, 0);
    _player_controlled_block.move(left);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        auto right = sf::Vector2f(-1 * left.x, -1 * left.y);
        _player_controlled_block.move(right);
    } else if(!auto_commit){
        auto right = sf::Vector2f(-1 * left.x, -1 * left.y);
        _player_controlled_block.move(right);
    }
}


bool Game::player_intersects_with_bounds() {
    bool down = _player_controlled_block.intersects(_bound_D);
    bool right = _player_controlled_block.intersects(_bound_R);
    bool left = _player_controlled_block.intersects(_bound_L);

    if (down || right || left){
        return true;
    } else{
        return false;
    }
}

bool Game::player_intersects_with_stack(){
    for (auto& stack_rectangle : _block_stack) {
        if (_player_controlled_block.intersects(stack_rectangle)){
            return true;
        }
    }
    return false;
}

void Game::gravity() {
    // Test will automatically move block if allowed (auto_commit = true)
    player_clear_to_move_down(true);
}


void Game::drop_player(){
    // Runs gravity tile_count_y number of times instantly to drop block
    for (int i = 0; i < Constants::tile_count_y; ++i) {
        gravity();
    }
}



void Game::try_placing_player() {
    bool can_move = player_clear_to_move_down();
    if (!can_move){
        _player_controlled_block.place();
    }
}


//====================================================================================================
//====================================================================================================
//====================================================================================================

void Game::do_action(int action) {

    switch (action) {
        case 0:
            move_player(action);
        case 1:
            move_player(action);
        case 2:
            move_player(action);
        case 3:
            drop_player();
        case 4:
            rotate_player();
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