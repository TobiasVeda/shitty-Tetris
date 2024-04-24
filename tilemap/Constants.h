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

    static inline const std::string tile_texture_name = "40frame.png";
    static inline const sf::Vector2u tilesize = sf::Vector2u(40, 40);
    static inline const sf::Vector2f gravity_strength = sf::Vector2f(0, 40); //related to tilesize
    static inline const unsigned int tile_count_x = 10;
    static inline const unsigned int tile_count_y = 18;
    static inline const auto game_tick = std::chrono::milliseconds(500);
    static inline const auto movement_speed = std::chrono::milliseconds(100);
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
    static void wait_movement_speed(){
        std::this_thread::sleep_for(movement_speed);
    }

};


#endif //TILEMAP_CONSTANTS_H
