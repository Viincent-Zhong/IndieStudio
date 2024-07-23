/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** GamePad.cpp
*/

#include <iostream>
#include <vector>
#include <map>
#include "raylib.h"
#include "GamePad.hpp"

RaylibGamePad::GamePad::GamePad()
{
}

RaylibGamePad::GamePad::~GamePad()
{
}


static const std::map<PadKey, GamepadButton> padKeys = {
    {PAD_LEFT, GAMEPAD_BUTTON_LEFT_FACE_LEFT},
    {PAD_RIGHT, GAMEPAD_BUTTON_LEFT_FACE_RIGHT},
    {PAD_UP, GAMEPAD_BUTTON_LEFT_FACE_UP},
    {PAD_DOWN, GAMEPAD_BUTTON_LEFT_FACE_DOWN},
    {PAD_X, GAMEPAD_BUTTON_RIGHT_FACE_LEFT},
    {PAD_Y, GAMEPAD_BUTTON_RIGHT_FACE_UP},
    {PAD_B, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT},
    {PAD_A, GAMEPAD_BUTTON_RIGHT_FACE_DOWN},
    {PAD_START, GAMEPAD_BUTTON_MIDDLE_RIGHT},
    {PAD_SELECT, GAMEPAD_BUTTON_MIDDLE_LEFT},
    {PAD_TRIGGER_LEFT, GAMEPAD_BUTTON_LEFT_TRIGGER_1},
    {PAD_TRIGGER_RIGHT, GAMEPAD_BUTTON_RIGHT_TRIGGER_1}};

bool RaylibGamePad::GamePad::isPadKeyDown(const int gamepad, PadKey key)
{
    if (!gamePadExist(gamepad))
        return false;

    if (key == PAD_LEFT && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return true;
    if (key == PAD_RIGHT && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return true;
    if (key == PAD_UP && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return true;
    if (key == PAD_DOWN && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return true;
    return IsGamepadButtonDown(gamepad, padKeys.find(key)->second);
}

bool RaylibGamePad::GamePad::isPadKeyReleased(const int gamepad, PadKey key)
{
    if (!gamePadExist(gamepad))
        return false;

    if (key == PAD_LEFT && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return true;
    if (key == PAD_RIGHT && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return true;
    if (key == PAD_UP && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return true;
    if (key == PAD_DOWN && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return true;
    return IsGamepadButtonReleased(gamepad, padKeys.find(key)->second);
}

int RaylibGamePad::GamePad::getTouchPress(const int gamepad)
{
    if (GetGamepadButtonPressed() == GAMEPAD_BUTTON_RIGHT_FACE_DOWN || GetGamepadButtonPressed() == 15)
        return KEY_ENTER;
    if (GetGamepadButtonPressed() == GAMEPAD_BUTTON_RIGHT_FACE_LEFT)
        return KEY_SPACE;
    if (GetGamepadButtonPressed() == GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)
        return KEY_N;
    return -1;
}

bool RaylibGamePad::GamePad::gamePadExist(const int gamepad)
{
    return IsGamepadAvailable(gamepad);
}

PadKey RaylibGamePad::GamePad::getPadKeyDown(const int gamepad)
{
    if (!gamePadExist(gamepad))
        return PAD_NOTHING;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_LEFT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_RIGHT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_UP;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_DOWN;
    for (auto it : padKeys) {
        if (IsGamepadButtonDown(gamepad, it.second))
            return it.first;
    }
    return PAD_NOTHING;
}

PadKey RaylibGamePad::GamePad::getPadKeyPressed(const int gamepad)
{
    if (!gamePadExist(gamepad))
        return PAD_NOTHING;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_LEFT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_RIGHT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_UP;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_DOWN;
    for (auto it : padKeys) {
        if (IsGamepadButtonPressed(gamepad, it.second))
            return it.first;
    }
    return PAD_NOTHING;
}

PadKey RaylibGamePad::GamePad::getPadKeyReleased(const int gamepad)
{
    if (!gamePadExist(gamepad))
        return PAD_NOTHING;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_LEFT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) < 0.5f)
        return PAD_RIGHT;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == -1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_UP;
    if (GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y) == 1.0f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) > -0.5f && GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X) < 0.5f)
        return PAD_DOWN;
    for (auto it : padKeys) {
        if (IsGamepadButtonPressed(gamepad, it.second))
            return it.first;
    }
    return PAD_NOTHING;
}