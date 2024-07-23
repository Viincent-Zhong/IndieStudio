/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Event.cpp
*/

#include "Event.hpp"

RaylibEvent::Event::Event()
{
}

RaylibEvent::Event::~Event()
{
}

int RaylibEvent::Event::getKeyInput() const
{
    return GetKeyPressed();
}

bool RaylibEvent::Event::mouseOnText(const float x, const float y, const float a, const float b)
{
    Rectangle rec = {x, y, a, b};

    return CheckCollisionPointRec(GetMousePosition(), rec);
}

bool RaylibEvent::Event::isKeyDown(const int key)
{
    return IsKeyDown(key);
}

bool RaylibEvent::Event::isKeyReleased(const int key)
{
    return IsKeyReleased(key);
}
