/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Music.cpp
*/

#include "Music.hpp"

RaylibMusic::MusicA::MusicA()
{
    _init = false;
    _isPlaying = false;
}

RaylibMusic::MusicA::~MusicA()
{
    if (_init)
        UnloadMusicStream(_music);
}

RaylibMusic::MusicA::MusicA(std::string const &path)
{
    _music = LoadMusicStream(path.c_str());
    _music.looping = true;
    _init = true;
    PlayMusicStream(_music);
    _isPlaying = true;
}

void RaylibMusic::MusicA::initMusic(std::string const &path, const float volume)
{
    _music = LoadMusicStream(path.c_str());
    _music.looping = false;
    _init = true;
    SetMusicVolume(_music, volume);
    PlayMusicStream(_music);
    _isPlaying = true;
}

void RaylibMusic::MusicA::stopMusic()
{
    StopMusicStream(_music);
}

void RaylibMusic::MusicA::pauseMusic()
{
    PauseMusicStream(_music);
}

void RaylibMusic::MusicA::resumeMusic()
{
    ResumeMusicStream(_music);
}

void RaylibMusic::MusicA::setMusicPitch(const float pitch)
{
    SetMusicPitch(_music, pitch);
}

void RaylibMusic::MusicA::setMusicVolume(const float volume)
{
    SetMusicVolume(_music, volume);
}

void RaylibMusic::MusicA::updateMusicStream()
{
    if (!IsMusicStreamPlaying(_music)) {
        PlayMusicStream(_music);
        _isPlaying = true;
    }
    UpdateMusicStream(_music);
}

bool RaylibMusic::MusicA::isPlaying() const
{
    return _isPlaying;
}
