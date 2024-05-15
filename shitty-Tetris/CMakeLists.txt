cmake_minimum_required(VERSION 3.27)
project(shitty-Tetris)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(shitty-Tetris main.cpp
        Tilemap.cpp
        Tilemap.h
        pieces/Base_shape.cpp
        pieces/Base_shape.h
        Constants.h
        pieces/T_block.cpp
        pieces/T_block.h
        pieces/O_block.cpp
        pieces/O_block.h
        Block_bag.cpp
        Block_bag.h
        pieces/L_block.cpp
        pieces/L_block.h
        Game.cpp
        Game.h
        pieces/all_pieces.h
        pieces/I_block.cpp
        pieces/I_block.h
        pieces/J_block.cpp
        pieces/J_block.h
        pieces/Z_block.cpp
        pieces/Z_block.h
        pieces/S_block.cpp
        pieces/S_block.h
        Keybinds.cpp
        Keybinds.h
        Process.cpp
        Process.h
        UI.cpp
        UI.h
)

target_link_libraries(shitty-Tetris PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
