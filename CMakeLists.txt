cmake_minimum_required (VERSION 2.6)
project (PowerDefense)

add_executable(PowerDefense main.cpp Tower.cpp Point.cpp Sprite.cpp)
target_link_libraries(PowerDefense -lSDL2 -lSDL2_image -lSDL2_ttf tmxparser)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_subdirectory(dependencies/tmxparser dependencies/tmxparser)
message(${CMAKE_MODULE_PATH})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/dependencies)
include_directories(dependencies/tmxparser/src)

add_definitions(-DCMAKE_SOURCE_DIR=std::string\("${CMAKE_SOURCE_DIR}"\))