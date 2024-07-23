/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Music.hpp
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <string>
#include "raylib.h"

namespace RaylibMusic {
class MusicA {
    public:
        /**
         * @brief Construct a new Music A object
         * handle mp3 files
         * 
         */
        MusicA();

        /**
         * @brief Construct a new Music A object
         * 
         * @param path 
         */
        MusicA(std::string const &path);

        /**
         * @brief Destroy the Music A object
         * 
         */
        ~MusicA();

        /**
         * @brief new Music object as the constructor
         * 
         * @param path 
         * @param volume 
         */
        void initMusic(std::string const &path, const float volume);

        /**
         * @brief end playing music
         * 
         */
        void stopMusic();

        /**
         * @brief pause the music
         * 
         */
        void pauseMusic();

        /**
         * @brief restart music after pause
         * 
         */
        void resumeMusic();

        /**
         * @brief Set the Music Pitch object
         * 
         * @param pitch 
         */
        void setMusicPitch(const float pitch);

        /**
         * @brief Set the Music Volume object
         * 
         * @param volume 
         */
        void setMusicVolume(const float volume);

        /**
         * @brief call everytime for play music
         * 
         */
        void updateMusicStream();

        /**
         * @brief return if the music is still playing
         * 
         * @return true 
         * @return false 
         */
        bool isPlaying() const;

    private:
        bool _init;
        bool _isPlaying;
        Music _music;
};
}

#endif /* !MUSIC_HPP_ */
