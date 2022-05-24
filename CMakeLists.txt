cmake_minimum_required(VERSION 3.17)
project(Snake VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(USE_FLAGS "-s USE_SDL=2")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${USE_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${USE_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${USE_FLAGS}")
	# For generating html
    # set(CMAKE_EXECUTABLE_SUFFIX .html)
else()
    find_package(SDL2 REQUIRED)
endif()
include_directories(${CMAKE_SOURCE_DIR}/include ${SDL2_INCLUDE_DIRS})

add_executable(Snake main.cpp objects.cpp setup.cpp)
target_link_libraries(Snake ${SDL2_LIBRARIES})

# https://trenki2.github.io/blog/2017/06/02/using-sdl2-with-cmake/
