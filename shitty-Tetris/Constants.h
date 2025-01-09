//
// Created by tobia on 20.04.2024.
//

#ifndef TILEMAP_CONSTANTS_H
#define TILEMAP_CONSTANTS_H

#include <SFML/Graphics.hpp>
#include <string>
#include <chrono>
#include <thread>

class Constants {
public:

    static inline const std::string texture_name = "assets/tileset.png";
    static inline const std::string title_texture = "assets/title.png";
    static inline const std::string favicon_name = "assets/favicon.png";
    static inline const std::string font_name = "assets/AgencyFB-Bold.ttf";
    static inline const std::string main_theme = "assets/korobeiniki.mp3";
    static inline const std::string lineclear_sound = "assets/lineclear.wav";
    static inline const std::string tetris_sound = "assets/tetris.wav";
    static inline const std::string placed_sound = "assets/placed.wav";
    static inline const float rotation_amount = 90;
    static inline const sf::Vector2u tilesize = sf::Vector2u(40, 40);
    static inline const unsigned int tile_count_x = 10;
    static inline const unsigned int tile_count_y = 18;
    static inline const int level_map[] = {
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

};

#endif //TILEMAP_CONSTANTS_H
