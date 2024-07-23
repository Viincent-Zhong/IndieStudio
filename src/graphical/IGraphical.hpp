/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** IGraphical.hpp
*/

#ifndef IGRAPHICAL_HPP_
#define IGRAPHICAL_HPP_

#include <vector>
#include <string>
#include <memory>
#include "raylib.h"

namespace IndieStudio {
    /**
     * @brief class for handle the basic method of raylib
     * @author Pierre-Alexandre Delgado
     * @date 08/06/22
     * @version 1.0
     * 
     */
    class IGraphical {
        public:
            /**
             * @brief Destroy the IGraphical object
             * 
             */
            virtual ~IGraphical() = default;

            /**
             * @brief Set the Fps object
             * 
             * @param fps 
             */
            virtual void setFps(unsigned int const &fps) = 0;

            /**
             * @brief enable the program to start drawing in the window
             * 
             * @param refresh true if you want to remove everything on the screen
             */
            virtual void startDrawing(const bool refresh) const = 0;

            /**
             * @brief stop the program to draw
             * 
             */
            virtual void endDrawing() const = 0;

            /**
             * @brief call after startDrawing, enable the program to draw in 3D
             * 
             */
            virtual void start3d() const = 0;

            /**
             * @brief stop the porgram to draw in 3d
             * 
             */
            virtual void end3d() const = 0;

            /**
             * @brief verify in the user close the window with escape or with the buttons
             * 
             * @return true the program continue
             * @return false the program stop
             */
            virtual bool endGame() = 0;

            /**
             * @brief Get the Frame Time object
             * 
             * @return float 
             */
            virtual float getFrameTime() = 0;

            /**
             * @brief adapt window size with the screen of the user
             * 
             */
            virtual void resizeWindow() = 0;

            /**
             * @brief Get the Music Volume in the program
             * 
             * @return float 
             */
            virtual float getMusicVolume() const = 0;

            /**
             * @brief Set the Music Volume in the program
             * 
             * @param volume 
             */
            virtual void setMusicVolume(const float volume) = 0;

            /**
             * @brief Set the Load Game object, true when you want to start with you're last game
             * 
             * @param load 
             */
            virtual void setLoadGame(const bool load) = 0;

            /**
             * @brief Get the Load object
             * 
             * @return true, start game with old game
             * @return false, start game with new parameters
             */
            virtual bool getLoad() const = 0;
            /**
             * @brief Set the Save state
             * 
             * @param save State of save (true if want to save, false otherwise)
             */
            virtual void setSave(const bool save) = 0;
            /**
             * @brief Get the Save state
             */
            virtual bool getSave() const = 0;
            /**
             * @brief Get the Window Size object
             * 
             * @return std::pair<int, int> 
             */
            virtual std::pair<int, int> getWindowSize() const = 0;

            /**
             * @brief Get the Effect Level object
             * 
             * @return float 
             */
            virtual float getEffectLevel() const = 0;

            /**
             * @brief Set the Effect Level object
             * 
             * @param level 
             */
            virtual void setEffectLevel(const float level) = 0;
    };
}

#endif /* !IGRAPHICAL_HPP_ */
