//
// Created by tobia on 21.05.2024.
//

#include "Audio.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

void Audio::load() {
    if (!_theme.openFromFile(Constants::main_theme)){
        throw std::exception("Unable to load BGM from disk");
    }
    _theme.setLoop(true);
    _theme.setVolume(50);

    if (!_lineclear_buffer.loadFromFile(Constants::lineclear_sound)){
        throw std::exception("Unable to load lineclear SFX into memory");
    }
    if (!_tetris_buffer.loadFromFile(Constants::tetris_sound)){
        throw std::exception("Unable to load tetris SFX into memory");
    }
    if (!_placed_buffer.loadFromFile(Constants::placed_sound)){
        throw std::exception("Unable to load block-placed SFX into memory");
    }

    _lineclear.setBuffer(_lineclear_buffer);
    _tetris.setBuffer(_tetris_buffer);
    _placed.setBuffer(_placed_buffer);
    _placed.setVolume(50);
}
void Audio::play_theme() {
    _theme.play();
}
void Audio::stop_theme() {
    _theme.pause();
}
void Audio::play_lineclear() {
    _lineclear.play();
}
void Audio::play_tetris() {
    _tetris.play();
}
void Audio::play_placed() {
    _placed.play();
}