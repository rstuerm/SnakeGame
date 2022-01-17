cmake_minimum_required(VERSION 3.17)
project(Snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Snake main.cpp objects.cpp setup.cpp)
target_link_libraries(Snake ${SDL2_LIBRARIES})

# https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
