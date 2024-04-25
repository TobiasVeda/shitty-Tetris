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
        Block_stack.cpp
        Block_stack.h
        pieces/O_block.cpp
        pieces/O_block.h
        Block_bag.cpp
        Block_bag.h
)

target_link_libraries(shitty-Tetris PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
