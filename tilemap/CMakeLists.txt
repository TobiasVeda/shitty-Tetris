cmake_minimum_required(VERSION 3.27)
project(tilemap)

set(CMAKE_CXX_STANDARD 17)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_executable(tilemap main.cpp
        Tilemap.cpp
        Tilemap.h
        Base_shape.cpp
        Base_shape.h
        Constants.h
        T_block.cpp
        T_block.h)

target_link_libraries(tilemap PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
