/*
** EPITECH PROJECT, 2021
** idistudio
** File description:
** Display.cpp
*/

#include <memory>
#include <iostream>
#include "Display.hpp"

Display::Display(unsigned int const screenWidth, unsigned int const screenHeight, std::string const &windowName, unsigned int const fps) : _screenWidth(screenWidth), _screenHeight(screenHeight)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(0, 0, windowName.c_str());
    MaximizeWindow();
    _camera = {{0.0f, 40.0f, 15.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, 30.0f, 0};
    SetCameraMode(_camera, CAMERA_FREE);
    setFps(fps);
    InitAudioDevice();
    _musicVolume = 1.0f;
    _effectLevel = 1.0f;
    _loadGame = false;
    _saveGame = false;
}

Display::~Display()
{
    CloseAudioDevice();
    CloseWindow();
}

std::pair<int, int> Display::getWindowSize() const
{
    return {GetScreenWidth(), GetScreenHeight()};
}

bool Display::endGame()
{
    return WindowShouldClose();
}

void Display::setFps(unsigned int const &fps)
{
    SetTargetFPS(fps);
}

void Display::startDrawing(const bool refresh) const
{
    BeginDrawing();
    if (refresh)
        ClearBackground(RAYWHITE);
}

void Display::endDrawing() const
{
    EndDrawing();
}

void Display::start3d() const
{
    BeginMode3D(_camera);
}

void Display::end3d() const
{
    EndMode3D();
}

float Display::getFrameTime()
{
    return GetFrameTime();
}

void Display::resizeWindow()
{
    if (IsWindowResized() && !IsWindowFullscreen()) {
        _screenWidth = GetScreenWidth();
        _screenHeight = GetScreenHeight();
    }
    if (IsWindowFullscreen()) {
        SetWindowSize(_screenWidth, _screenHeight);
    } else {
        int display = GetCurrentMonitor();
        SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
    }
}

float Display::getMusicVolume() const
{
    return _musicVolume;
}

void Display::setMusicVolume(const float volume)
{
    _musicVolume = volume;
}

void Display::setLoadGame(const bool load)
{
    _loadGame = load;
}

bool Display::getLoad() const
{
    return _loadGame;
}

bool Display::getSave() const
{
    return _saveGame;
}

void Display::setSave(const bool save)
{
    _saveGame = save;
}

float Display::getEffectLevel() const
{
    return _effectLevel;
}

void Display::setEffectLevel(const float level)
{
    _effectLevel = level;
}
