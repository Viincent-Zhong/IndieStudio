/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Button.hpp
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <string>
#include <vector>
#include "GamePad/GamePad.hpp"
#include "raylib.h"

namespace RaylibButton {
    /**
     * @brief class for create buttons in raylib and handle them
     * handle .PNG files
     * 
     */
    class Button {
        public:
            /**
             * @brief Construct a new Button object
             * 
             */
            Button();

            /**
             * @brief Construct a new Button object with params
             * 
             * @param path 
             * @param pathHover 
             * @param pos 
             * @param sound 
             * @param volumeSound 
             */
            Button(std::string const &path, std::string const &pathHover, std::pair<float, float> const &pos, std::string const &sound, const float volumeSound);

            /**
             * @brief Destroy the Button object
             * 
             */
            ~Button();

            /**
             * @brief create new Button object, as the constructor with params
             * 
             * @param path 
             * @param pathHover 
             * @param pos 
             * @param sound 
             * @param volumeSound 
             */
            void create(std::string const &path, std::string const &pathHover, std::pair<float, float> const &pos, std::string const &sound, const float volumeSound);

            /**
             * @brief change texture of the Button object
             * 
             * @param texture 
             * @param pos 
             */
            void update(std::string const &texture, std::pair<float, float> const &pos);

            /**
             * @brief print the Button object on the window
             * 
             */
            void display();

            /**
             * @brief anim the Button object, when click or the mouse is hover it
             * 
             */
            void animation();

            /**
             * @brief return the status of Button object, if press or not
             * 
             * @return true 
             * @return false 
             */
            bool isPress();

            /**
             * @brief Set the Effect Level object, change the volume of sound when press
             * 
             * @param level 
             */
            void setEffectLevel(const float level);

        protected:
        private:
            Sound _sound;
            std::vector<Texture2D> _texture;
            std::vector<float> _frameHeight;
            std::vector<Rectangle> _sourceRec;
            std::vector<Rectangle> _btnBounds;
            bool _isPress;
            int _buttonState;
            RaylibGamePad::GamePad _gamepad;
    };
}

#endif /* !BUTTON_HPP_ */
