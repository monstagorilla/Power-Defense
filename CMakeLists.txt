cmake_minimum_required (VERSION 2.6)
project (PowerDefense)

add_executable(PowerDefense Tower.cpp main.cpp  Point.cpp Sprite.cpp Map.cpp Enemy.cpp Shot.cpp Button.cpp GUIObject.cpp BasicTower.cpp Label.cpp MapOverlay.cpp GameObject.cpp GUI.cpp GUIFunctions.cpp eventHandler.cpp BasicEnemy.cpp BasicEnemy.h TextOutput.cpp Cache.cpp Symbol.cpp Symbol.h)
target_link_libraries(PowerDefense -lSDL2 -lSDL2_image -lSDL2_ttf tmxparser)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

add_subdirectory(dependencies/tmxparser dependencies/tmxparser)
message(${CMAKE_MODULE_PATH})

include_directories(${CMAKE_CURRENT_BINARY_DIR}/dependencies)
include_directories(dependencies/tmxparser/src)

add_definitions(-DCMAKE_SOURCE_DIR=std::string\("${CMAKE_SOURCE_DIR}"\))
