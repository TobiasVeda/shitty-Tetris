//
// Created by tobia on 26.04.2024.
//

#include "Game.h"
#include "Constants.h"
#include "Block_bag.h"
#include "Keybinds.h"
#include <vector>

Game::Game(int player) {

    _view.setSize(sf::Vector2f(600, 720));
    _view.setCenter(sf::Vector2f(300,360));
    if (player == 0){
        _view.setViewport(sf::FloatRect(0.356f, 0.1, 0.36f, 0.75));
    } else if (player == 1){
        _view.setViewport(sf::FloatRect(0.13f, 0.1, 0.36f, 0.75));
    } else if (player == 2){
        _view.setViewport(sf::FloatRect(0.63f, 0.1, 0.36f, 0.75));
    }

    _player_controlled_block = Block_bag::get_new_block();
    _held_this_turn = false;
    _held_blocktype = Constants::Ndef;

    _score = 0;
    _level = 1;
    _lines_cleared = 0;
    _is_dead = false;

    set_bounds();
}

Game::~Game() noexcept {
    delete _player_controlled_block;
}

void Game::set_bounds() {
    auto size_L_R = sf::Vector2f(1, _view.getSize().y + 2);
    auto size_B = sf::Vector2f(_view.getSize().x + 2, 1);

    _bound_L.setSize(size_L_R);
    _bound_R.setSize(size_L_R);
    _bound_D.setSize(size_B);

    _bound_L.setPosition(
            _view.getCenter().x - (_view.getSize().x /2) - _bound_L.getSize().x,
            _view.getCenter().y - (_view.getSize().y /2)
            );
    _bound_R.setPosition(
            _view.getCenter().x - (_view.getSize().x /2) + (Constants::tilesize.x * Constants::tile_count_x),
            _view.getCenter().y - (_view.getSize().y /2)
            );
    _bound_D.setPosition(
            _view.getCenter().x - (_view.getSize().x /2) -1,
            _view.getCenter().y + (_view.getSize().y /2)
            );
}




void Game::add_player_to_collection() {
    // Does not check for duplicates. Should be sure that rectangles added does
    // not overlap with already existing rectangles.
    for (const auto& i : _player_controlled_block->get_rectangle_list()) {
        _block_stack.emplace_back(i);
    }
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(*_player_controlled_block, states);

    for (auto& i : _block_stack) {
            target.draw(i, states);
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
        _player_controlled_block->move(down);
        _score += calculate_move_points();
    }
    if (direction == Constants::Right && next_pos_valid_right){
        auto right = sf::Vector2f( (float)Constants::tilesize.y, 0);
        _player_controlled_block->move(right);
    }
    if (direction == Constants::Left && next_pos_valid_left){
        auto left = sf::Vector2f(-1 * (float)Constants::tilesize.y, 0);
        _player_controlled_block->move(left);
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
    _player_controlled_block->move(down);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block->move(up);
        return false;
    } else if(!auto_commit){
        _player_controlled_block->move(up);
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
    _player_controlled_block->move(right);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block->move(left);
        return false;
    } else if(!auto_commit){
        _player_controlled_block->move(left);
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
    _player_controlled_block->move(left);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block->move(right);
        return false;
    } else if(!auto_commit){
        _player_controlled_block->move(right);
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
    _player_controlled_block->rotate(clockwise);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block->rotate(counter_clock);
        return false;
    } else if(!auto_commit){
        _player_controlled_block->rotate(counter_clock);
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
    _player_controlled_block->rotate(counter_clock);

    if (player_intersects_with_bounds() || player_intersects_with_stack()){
        _player_controlled_block->rotate(clockwise);
        return false;
    } else if(!auto_commit){
        _player_controlled_block->rotate(clockwise);
        return true;
    }
    return true;
}


bool Game::player_intersects_with_bounds() {
    bool down = _player_controlled_block->intersects(_bound_D);
    bool right = _player_controlled_block->intersects(_bound_R);
    bool left = _player_controlled_block->intersects(_bound_L);

    if (down || right || left){
        return true;
    } else{
        return false;
    }
}

bool Game::player_intersects_with_stack(){
    for (auto& stack_rectangle : _block_stack) {
        if (_player_controlled_block->intersects(stack_rectangle)){
            return true;
        }
    }
    return false;
}

bool Game::gravity() {
    // Test will automatically move block if allowed (auto_commit = true)
    return player_clear_to_move_down(true);
}


void Game::drop_player(){
    // Runs gravity tile_count_y number of times instantly to drop block
    for (int i = 0; i < Constants::tile_count_y; ++i) {
        if (gravity()){
            _score += calculate_drop_points();
        }
    }
    _player_controlled_block->place();
}



void Game::try_placing_player(){
    bool can_move = player_clear_to_move_down();
    if (!can_move){
        _player_controlled_block->place();
    }
}

void Game::try_death(){
    if (player_intersects_with_stack()){
        _is_dead = true;
    }
}
void Game::new_round(){
    add_player_to_collection();
    try_lineclear();
    try_levelup();
    _player_controlled_block = Block_bag::get_new_block();
    try_death();
    _held_this_turn = false;
}
void Game::end_game(){
    exit(9);
}
void Game::do_gametick_action() {
    // Test if placed first to allow block to move when it hits bottom.

    if (_is_dead){
        end_game();
    }
    if (_player_controlled_block->is_placed()){
        new_round();
    }
    gravity();
    try_placing_player();
}

void Game::do_action(Constants::Actions action) {

    switch (action) {
        case Constants::Move_down:
            move_player(Constants::Directions::Down);
            break;
        case Constants::Move_right:
            move_player(Constants::Directions::Right);
            break;
        case Constants::Move_left:
            move_player(Constants::Directions::Left);
            break;
        case Constants::Rotate_clockwise:
            rotate_player(Constants::Rotation_direction::Clockwise);
            break;
        case Constants::Rotate_counter_clock:
            rotate_player(Constants::Rotation_direction::Counter_clock);
            break;
        case Constants::Drop:
            drop_player();
            break;
        case Constants::Hold:
            if (!_held_this_turn){
                hold_player();
            }
            break;
        case Constants::Nothing:
            break;
    }
}

void Game::hold_player(){
    // If first call: The type of player block is stored, and player is given a new block.
    // If not first call: Player type is stored, and player is given a new block with the previous stored type.
    _held_this_turn = true;
    if (_held_blocktype == Constants::Ndef){
        _held_blocktype = _player_controlled_block->get_blocktype();
        _player_controlled_block = Block_bag::get_new_block();
    } else{
        Constants::Block_types temp_type = _held_blocktype;
        _held_blocktype = _player_controlled_block->get_blocktype();
        _player_controlled_block = Block_bag::get_new_block(temp_type);
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

void Game::try_levelup(){
    // 10 lines cleared increases the level by 1.
    float new_level = ((float)_lines_cleared / 10 ) + 1;
    _level = floor(new_level);
}

int Game::calculate_clear_points(int lines_count){
    // A block have the maximum length of 4.

    if (lines_count == 1){
        return 100 * _level;
    } else if (lines_count == 2){
        return 300 * _level;
    } else if (lines_count == 3){
        return 500 * _level;
    } else if(lines_count == 4){
        return 800 * _level;
    } else{
        return 0;
    }
}

int Game::calculate_drop_points(){
    return 2 * _level;
}

int Game::calculate_move_points(){
    return 1 * _level;
}

std::vector<int> Game::get_scoreboard(){
    return std::vector{_score, _level, _lines_cleared};
}

void Game::try_lineclear(){
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
    _score += calculate_clear_points((int)coord_line_cleared.size());
    _lines_cleared += (int)coord_line_cleared.size();
    move_lines_down(coord_line_cleared);
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

Constants::Block_types Game::get_held_type(){
    return _held_blocktype;
}

void Game::move_lines_down(std::vector<int> &coord_line_cleared) {
    // Moves all rectangles in stack that has y coordinate greater than specified.
    // The y coordinate is the y coordinate of the line that was just cleared. If multiple lines was cleared,
    // it moves the stack down for each line cleared

    std::reverse(coord_line_cleared.begin(), coord_line_cleared.end());
    sf::Vector2f block_check;
    const auto bottom_left = sf::Vector2f(
            _view.getCenter().x - (_view.getSize().x /2) +1,
            _view.getCenter().y + (_view.getSize().y /2) -1
    ); // +-1 because contains does not check edges of shape

    for (int z = 0; z < coord_line_cleared.size(); ++z) {


        for (int y = coord_line_cleared[z]; y < Constants::tile_count_y; ++y) {

            for (int x = 0; x < Constants::tile_count_x; ++x) {
                block_check = sf::Vector2f(
                        bottom_left.x + (x * Constants::tilesize.x),
                        bottom_left.y - (y * Constants::tilesize.y)
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

double Game::get_gravity_delay_ms() {
    // https://harddrop.com/wiki/Tetris_Worlds#Gravity
    double delay_s = pow((0.8-((_level-1)*0.007)), (double)(_level-1));
    return delay_s * 1000;
}

sf::View& Game::get_view() {
    return _view;
}
