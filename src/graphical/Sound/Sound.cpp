/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Sound.cpp
*/

#include "Sound.hpp"

RaylibSound::MySound::MySound() : _init(false)
{
}

RaylibSound::MySound::~MySound()
{
    //if (_init)
    //    UnloadSound(_sound);
}

void RaylibSound::MySound::create(std::string const &path)
{
    _init = true;
    _sound = LoadSound(path.c_str());
}

void RaylibSound::MySound::playSound()
{
    PlaySound(_sound);
}

void RaylibSound::MySound::updateVolume(const float volume)
{
    SetSoundVolume(_sound, volume);
}
