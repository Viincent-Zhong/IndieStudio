/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Text.hpp
*/

#ifndef TEXT_HPP_
#define TEXT_HPP_

#include <string>
#include "raylib.h"

namespace RaylibText {
    /**
     * @brief class for print text in Raylib
     * 
     */
    class Text {
        public:
            /**
             * @brief Construct a new Text object
             * 
             */
            Text();

            /**
             * @brief Construct a new Text object
             * 
             * @param path 
             */
            Text(std::string const &path);

            /**
             * @brief Destroy the Text object
             * 
             */
            ~Text();

            /**
             * @brief Load font, call at the beginning
             * 
             * @param path to the font
             */
            void loadFont(std::string const &path);

            /**
             * @brief 
             * 
             * @param text 
             * @param pos X Y
             * @param color Raylib color
             * @param size multiplicator for size
             */
            void printText(std::string const &text, std::pair<float, float> const &pos, Color const color, const unsigned int size) const;

        private:
            Font _font;
            bool _init;
    };
}

#endif /* !TEXT_HPP_ */
