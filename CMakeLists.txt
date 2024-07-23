##
## EPITECH PROJECT, 2022
## indie studio
## File description:
## Main CMakeLists

cmake_minimum_required(VERSION 3.17)

cmake_policy(VERSION 3.17)

set(CMAKE_BUILD_TYPE Release)

project(Bomberman VERSION 1.0
        DESCRIPTION "Indie studio bomberman"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SRCS
        Main.cpp
        src/graphical/Display.cpp
        src/graphical/Button/Button.cpp
        src/graphical/Element/Element.cpp
        src/graphical/Event/Event.cpp
        src/graphical/Map/Map.cpp
        src/graphical/Music/Music.cpp
        src/graphical/Text/Text.cpp
        src/graphical/Image/Image.cpp
        src/graphical/Sound/Sound.cpp
        src/graphical/GamePad/GamePad.cpp
        src/scenes/SceneHandler.cpp
        src/scenes/Game/SceneGame.cpp
        src/scenes/Game/initGame.cpp
        src/scenes/Menu/SceneMenu.cpp
        src/scenes/Params/SceneParams.cpp
        src/scenes/Pause/ScenePause.cpp
        src/scenes/Selection/SceneSelection.cpp
        src/scenes/Recap/SceneRecap.cpp
        src/Entity/Player.cpp
        src/Parser/Parser.cpp
        src/Entity/IA.cpp
        src/Entity/Bomb.cpp
        src/Error/Error.cpp
        src/PlayMap.cpp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

FIND_PACKAGE(raylib REQUIRED)

add_executable(bomberman ${SRCS})

TARGET_LINK_LIBRARIES(bomberman raylib)

target_include_directories(bomberman PUBLIC include)
target_include_directories(bomberman PUBLIC include/scenes)
target_include_directories(bomberman PUBLIC include/Error)
target_include_directories(bomberman PUBLIC src/graphical)

set_target_properties(bomberman PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
