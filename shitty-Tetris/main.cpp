#include "Process.h"
#include <thread>
#include "Constants.h"

//TODO: Fix include order, add const when what the function recieves shouldnt be edited
//all things relative to view will break when view is expanded to include "next blocks" and "hold".
//      can probably still use center, but must expand from center with tilesize * tilecount_x/y
// make move diagonal possible
//TODO: Error handling when not finding texture, key_hold for multiple inputs
// Switchcase in player controller?
//TODO: move_line_down fix, Game::new_round is_placed logic
// first hold displays T but is empty. UI magic numbers



int main(){
    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "shitty Tetris");
    window.setActive(false);

    while (window.isOpen()) {

        sf::Event event{};
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        Process::game_loop(window, 0);
        Constants::wait_game_tick();
    }

//    static std::thread p1(Process::game_loop, std::ref(window), 0);
//    p1.join();
//    (miltiplayer, p1/p2 opt)
//    std::thread p2(Process::game_loop, 2);

//    p1.join();
//    p2.join();
}

