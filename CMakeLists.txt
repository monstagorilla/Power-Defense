cmake_minimum_required (VERSION 2.6)
project (PowerDefense)

add_subdirectory(dependencies/tmxparser)

add_definitions(-DCMAKE_SOURCE_DIR=std::string\("${CMAKE_SOURCE_DIR}"\))

add_executable(PowerDefense main.cpp Tower.cpp Point.cpp Sprite.cpp)
target_link_libraries(PowerDefense -lSDL2 -lSDL2_image tmxparser)

