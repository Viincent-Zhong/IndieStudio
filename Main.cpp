/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** main.cpp
*/

#include "Display.hpp"
#include "SceneHandler.hpp"

int main(int ac, char **av)
{
    Display display(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_NAME, FPS);
    SceneHandler handler(display);

    if (handler.run(display).first == -1)
        return 84;
    return 0;
}
