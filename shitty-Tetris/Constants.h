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
    enum Directions{Down, Right, Left};
    enum Rotation_direction{Clockwise, Counter_clock};
    enum Actions{Move_down, Move_right, Move_left, Rotate_clockwise, Rotate_counter_clock, Drop, Hold, Nothing};
    enum Block_types{T, O, L, I, J, Z, S, Ndef};
    enum Game_states{Setup, Run, End};
    static inline const std::string texture_name = "tileset.png";
    static inline const std::string title_texture = "title.png";
    static inline const std::string font_name = "AgencyFB-Bold.ttf";
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
