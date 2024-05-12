//
// Created by tobia on 26.04.2024.
//

#include "Game.h"
#include <string>
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
    bool next_pos_valid_down = player_clear_to_move_down();
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

void Game::rotate_player(Constants::Rotation_direction direction){
    switch (direction) {
        case Constants::Clockwise:
            player_clear_to_rotate_clockwise(true);
            break;
        case Constants::Counter_clock:
            player_clear_to_rotate_counter_clock(true);
            break;
    }
}

bool Game::player_clear_to_move_down(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto down = sf::Vector2f(0, (float)Constants::tilesize.y);
    auto up = sf::Vector2f(-1 * down.x, -1 * down.y);
    _player_controlled_block.move(down);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block.move(up);
        return false;
    } else if(!auto_commit){
        _player_controlled_block.move(up);
        return true;
    }
    return true;
}
bool Game::player_clear_to_move_right(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto right = sf::Vector2f((float)Constants::tilesize.x, 0);
    auto left = sf::Vector2f(-1 * right.x, -1 * right.y);
    _player_controlled_block.move(right);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block.move(left);
        return false;
    } else if(!auto_commit){
        _player_controlled_block.move(left);
        return true;
    }
    return true;
}
bool Game::player_clear_to_move_left(bool auto_commit){
    // If auto_commit is set to true, the function will not set the block's
    // position back to the position it had before the function.
    // If auto_commit is false, the block must be moved manually later

    auto left = sf::Vector2f(-1 * (float)Constants::tilesize.x, 0);
    auto right = sf::Vector2f(-1 * left.x, -1 * left.y);
    _player_controlled_block.move(left);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block.move(right);
        return false;
    } else if(!auto_commit){
        _player_controlled_block.move(right);
        return true;
    }
    return true;
}

bool Game::player_clear_to_rotate_clockwise(bool auto_commit){
    // If auto_commit is set to true, the function will not rotate the block
    // back to the rotation it had before the function.
    // If auto_commit is false, the block must be rotated manually later

    float clockwise = Constants::rotation_amount;
    float counter_clock = -1 * clockwise;
    _player_controlled_block.rotate(clockwise);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block.rotate(counter_clock);
        return false;
    } else if(!auto_commit){
        _player_controlled_block.rotate(counter_clock);
        return true;
    }
    return true;
}

bool Game::player_clear_to_rotate_counter_clock(bool auto_commit){
    // If auto_commit is set to true, the function will not rotate the block
    // back to the rotation it had before the function.
    // If auto_commit is false, the block must be rotated manually later

    float counter_clock = -1 * Constants::rotation_amount;
    float clockwise = -1 * counter_clock;
    _player_controlled_block.rotate(counter_clock);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block.rotate(clockwise);
        return false;
    } else if(!auto_commit){
        _player_controlled_block.rotate(clockwise);
        return true;
    }
    return true;
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



void Game::try_placing_player(){
    bool can_move = player_clear_to_move_down();
    if (!can_move){
        _player_controlled_block.place();
    }
}

sf::RenderWindow& Game::get_window() {
    return _window;
}


void Game::do_action(Constants::Actions action) {

    switch (action) {
        case Constants::Nothing:
            return;
        case Constants::Move_down:
            move_player(Constants::Down);
            break;
        case Constants::Move_right:
            move_player(Constants::Right);
            break;
        case Constants::Move_left:
            move_player(Constants::Left);
            break;
        case Constants::Rotate_clockwise:
            rotate_player(Constants::Clockwise);
            break;
        case Constants::Rotate_counter_clock:
            rotate_player(Constants::Counter_clock);
            break;
        case Constants::Drop:
            drop_player();
            break;
    }

}
bool Game::is_filled(sf::Vector2f &check_coord) {
    for (auto& i : _block_stack) {
        if (i.getGlobalBounds().contains(check_coord)){
            return true;
        }
    }
    return false;
}

void Game::try_lineclear() {
    sf::Vector2f check_coord;
    std::vector<int> coord_line_cleared;

    // Gets bottom left of view by getting center and moving half width to the left and half height down
    const auto bottom_left = sf::Vector2f(
            _view.getCenter().x - (_view.getSize().x /2) +1,
            _view.getCenter().y + (_view.getSize().y /2) -1
    ); // +-1 because "contains" does not check edges of shape


    for (int y = 0; y < Constants::tile_count_y; ++y) {
        int fill_count = 0;

        for (int x = 0; x < Constants::tile_count_x; ++x) {
            // Moves the point x tiles left and y tiles up
            check_coord = sf::Vector2f(
                    bottom_left.x + (float)(x * Constants::tilesize.x),
                    bottom_left.y - (float)(y * Constants::tilesize.y)
            );

            if (!is_filled(check_coord)){
                break;
            } else{
                fill_count++;
            }
            // Fill count is equal to the width of the board which means a line is full.
            // Emplace_back how many lines are below the full line.
            // Clears the row at the current y level
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
    // Loops through a line at given y level and clears all rectangles.

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

        for (auto i = _block_stack.begin(); i != _block_stack.end(); ++i) {
                if (i->getGlobalBounds().contains(check_coord)){
                    _block_stack.erase(i);
                    break;
                }
        }

    }

}

void Game::move_line_down(std::vector<int> &coord_line_cleared) {
    // Doesnt always work, yet

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

                        if (i.getGlobalBounds().contains(block_check)){
                            i.move(0, Constants::tilesize.y);
                            break;
                        }
                }
            }
        }
    }

}
