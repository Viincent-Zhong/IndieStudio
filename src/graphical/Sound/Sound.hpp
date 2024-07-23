/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Sound.hpp
*/

#ifndef MySOUND_HPP_
#define MySOUND_HPP_

#include <string>
#include "raylib.h"

namespace RaylibSound {
    /**
     * @brief class for play Sound as explosion, click on buttons, kill someone...
     * handle WAV files
     * 
     */
    class MySound {
        public:
            /**
             * @brief Construct a new My Sound object
             * 
             */
            MySound();

            /**
             * @brief Destroy the My Sound object
             * 
             */
            ~MySound();

            /**
             * @brief create Sound object as the constructor
             * 
             * @param path 
             */
            void create(std::string const &path);

            /**
             * @brief play Sound
             * 
             */
            void playSound();

            /**
             * @brief change sound voluem
             * 
             * @param volume 
             */
            void updateVolume(const float volume);

        private:
            Sound _sound;
            bool _init;
    };
}

#endif /* !MySOUND_HPP_ */
