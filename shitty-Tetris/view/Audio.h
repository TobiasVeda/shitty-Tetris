//
// Created by tobia on 21.05.2024.
//

#ifndef SHITTY_TETRIS_AUDIO_H
#define SHITTY_TETRIS_AUDIO_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Audio {
private:
    static inline sf::SoundBuffer _lineclear_buffer;
    static inline sf::SoundBuffer _tetris_buffer;
    static inline sf::SoundBuffer _placed_buffer;

    static inline sf::Music _theme;
    static inline sf::Sound _lineclear;
    static inline sf::Sound _tetris;
    static inline sf::Sound _placed;

public:
    static void load();
    static void play_theme();
    static void stop_theme();
    static void play_lineclear();
    static void play_tetris();
    static void play_placed();
};


#endif //SHITTY_TETRIS_AUDIO_H
