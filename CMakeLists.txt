cmake_minimum_required (VERSION 2.6)
project (PowerDefense)
add_executable(PowerDefense main.cpp Tower.cpp Point.cpp Sprite.cpp)
target_link_libraries(PowerDefense -lSDL2 -lSDL2_image)
