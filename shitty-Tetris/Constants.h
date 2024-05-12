//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_CONSTANTS_H
#define TILEMAP_CONSTANTS_H

#include <string>
#include <chrono>
#include <thread>



class Constants {
public:
    enum Directions{Down = 0, Right = 1, Left = 2};
    enum Block_types{T=0, O=1, L=2, I=3, J=4, Z=5, S=6};
    static inline const std::string texture_name = "tileset.png";
    static inline const sf::Vector2u tilesize = sf::Vector2u(40, 40);
    static inline const sf::Vector2f gravity_strength = sf::Vector2f(0, 40); //related to tilesize
    static inline const unsigned int tile_count_x = 10;
    static inline const unsigned int tile_count_y = 18;
    static inline const auto game_tick = std::chrono::milliseconds(75);
//    a short game tick is 100ms, but only move and draw run at that,
//    most other major events run at a longer interval (long_game_tick)
//    such as gravity and line clear
    static        const int long_game_tick = 10;
    static        const int short_game_tick = 2;
    constexpr static const int level_map[] = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };

    static void wait_game_tick(){
        std::this_thread::sleep_for(game_tick);
    }

};


#endif //TILEMAP_CONSTANTS_H
