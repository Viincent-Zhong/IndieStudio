/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Image.hpp
*/

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <string>
#include "raylib.h"

namespace RaylibImage {
    /**
     * @brief class for handle Image as logo, icons...
     * handle PNG files
     * 
     */
    class Image {
        public:
            /**
             * @brief Construct a new Image object
             * 
             */
            Image();

            /**
             * @brief Construct a new Image object
             * 
             * @param path 
             */
            Image(std::string const &path);

            /**
             * @brief Destroy the Image object
             * 
             */
            ~Image();

            /**
             * @brief create new Image as the constructor
             * 
             * @param path 
             */
            void create(std::string const &path);

            /**
             * @brief display the Image at pos
             * 
             * @param pos X Y on the screen
             * @param size multiplicator for the image size
             */
            void display(std::pair<float, float> const &pos, const float size);

        private:
            bool _init;
            Texture2D _image;
    };
}

#endif /* !IMAGE_HPP_ */
