/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** Button.cpp
*/

#include "GamePad/GamePad.hpp"
#include "Button.hpp"

RaylibButton::Button::Button()
{
    _buttonState = 0;
    _isPress = false;
}

RaylibButton::Button::Button(std::string const &path, std::string const &pathHover, std::pair<float, float> const &pos, std::string const &sound, const float volumeSound) : _buttonState(0), _isPress(false)
{
    _texture.push_back(LoadTexture(path.c_str()));
    _frameHeight.push_back((float)_texture.at(0).height);
    _sourceRec.push_back({0, 0, (float)_texture.at(0).width, _frameHeight.at(0)});
    _btnBounds.push_back({ pos.first, pos.second, (float)_texture.at(0).width, _frameHeight.at(0)});
    _texture.push_back(LoadTexture(pathHover.c_str()));
    _frameHeight.push_back((float)_texture.at(1).height);
    _sourceRec.push_back({0, 0, (float)_texture.at(1).width, _frameHeight.at(1)});
    _btnBounds.push_back({ pos.first, pos.second, (float)_texture.at(1).width, _frameHeight.at(1)});
    _sound = LoadSound(sound.c_str());
    SetSoundVolume(_sound, volumeSound);
}

RaylibButton::Button::~Button()
{
    UnloadTexture(_texture.at(0));
    UnloadTexture(_texture.at(1));
    UnloadSound(_sound);
}

void RaylibButton::Button::create(std::string const &path, std::string const &pathHover, std::pair<float, float> const &pos, std::string const &sound, const float volumeSound)
{
    _buttonState = 0;
    _texture.push_back(LoadTexture(path.c_str()));
    _frameHeight.push_back((float)_texture.at(0).height);
    _sourceRec.push_back({0, 0, (float)_texture.at(0).width, _frameHeight.at(0)});
    _btnBounds.push_back({ pos.first, pos.second, (float)_texture.at(0).width, _frameHeight.at(0)});
    _texture.push_back(LoadTexture(pathHover.c_str()));
    _frameHeight.push_back((float)_texture.at(1).height);
    _sourceRec.push_back({0, 0, (float)_texture.at(1).width, _frameHeight.at(1)});
    _btnBounds.push_back({ pos.first, pos.second, (float)_texture.at(1).width, _frameHeight.at(1)});
    _isPress = false;
    _sound = LoadSound(sound.c_str());
    SetSoundVolume(_sound, volumeSound);
}

void RaylibButton::Button::update(std::string const &texture, std::pair<float, float> const &pos)
{
    _texture.at(0) = LoadTexture(texture.c_str());
    _texture.at(1) = LoadTexture(texture.c_str());
    _sourceRec.at(0) = {0, 0, (float)_texture.at(0).width, _frameHeight.at(0)};
    _btnBounds.at(0) = { pos.first, pos.second, (float)_texture.at(0).width, _frameHeight.at(0)};
    _sourceRec.at(1) = {0, 0, (float)_texture.at(1).width, _frameHeight.at(1)};
    _btnBounds.at(1) = { pos.first, pos.second, (float)_texture.at(1).width, _frameHeight.at(1)};
}

void RaylibButton::Button::display()
{
    Vector2 vector = {_btnBounds.at(_buttonState).x, _btnBounds.at(_buttonState).y};

    DrawTextureRec(_texture.at(_buttonState), _sourceRec.at(_buttonState), vector, WHITE);
}

void RaylibButton::Button::animation()
{
    if (CheckCollisionPointRec(GetMousePosition(), _btnBounds.at(_buttonState))) {
        _buttonState = 1;
        _isPress = false;
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || _gamepad.isPadKeyDown(0, PAD_A))
            PlaySound(_sound);
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || _gamepad.isPadKeyReleased(0, PAD_A))
            _isPress = true;
    } else {
        _isPress = false;
        _buttonState = 0;
    }
}

bool RaylibButton::Button::isPress()
{
    if (_isPress) {
        _isPress = false;
        return true;
    }
    return false;
}

void RaylibButton::Button::setEffectLevel(const float level)
{
    SetSoundVolume(_sound, level);
}
