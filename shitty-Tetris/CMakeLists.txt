cmake_minimum_required(VERSION 3.27)
project(shitty-Tetris)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

add_executable(shitty-Tetris main.cpp
        view/Tilemap.cpp
        view/Tilemap.h
        model/pieces/Base_shape.cpp
        model/pieces/Base_shape.h
        Constants.h
        model/pieces/T_block.cpp
        model/pieces/T_block.h
        model/pieces/O_block.cpp
        model/pieces/O_block.h
        Block_bag.cpp
        Block_bag.h
        model/pieces/L_block.cpp
        model/pieces/L_block.h
        model/Game.cpp
        model/Game.h
        model/pieces/all_pieces.h
        model/pieces/I_block.cpp
        model/pieces/I_block.h
        model/pieces/J_block.cpp
        model/pieces/J_block.h
        model/pieces/Z_block.cpp
        model/pieces/Z_block.h
        model/pieces/S_block.cpp
        model/pieces/S_block.h
        model/Keybinds.cpp
        model/Keybinds.h
        controller/Player_instance.cpp
        controller/Player_instance.h
        view/UI.cpp
        view/UI.h
        view/Main_menu.cpp
        view/Main_menu.h
        view/Audio.cpp
        view/Audio.h
        controller/Process.cpp
        controller/Process.h
)

target_link_libraries(shitty-Tetris PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
