/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Map.hpp
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <string>
#include "raylib.h"

namespace RaylibMap {
    struct saveMap {
        char map[50];
        char texture[50];
    };

    class Map {
        public:
            /**
             * @brief Construct a new Map object
             * Map is a PNG file with pixel in black of white
             * 
             */
            Map();

            /**
             * @brief Construct a new Map object
             * 
             * @param map 
             * @param texture 
             */
            Map(std::string const &map, std::string const &texture);

            /**
             * @brief Destroy the Map object
             * 
             */
            ~Map();

            /**
             * @brief init map as the constructor
             * 
             * @param map 
             * @param texture 
             */
            void initMap(std::string const &map, std::string const &texture);

            /**
             * @brief draw Map object
             * 
             */
            void drawMap();

            /**
             * @brief Get the Position object
             * 
             * @return Vector3 
             */
            Vector3 getPosition() const;

            /**
             * @brief Get the Texture object
             * 
             * @return Texture2D 
             */
            Texture2D getTexture() const;

            /**
             * @brief Get the Pixels object
             * 
             * @return Color* 
             */
            Color *getPixels() const;
            /**
             * @brief Get the image of the map (a filepath)
             */
            std::string getMapImage() const;
            /**
             * @brief Get the texture filepath
             * 
             */
            std::string getTextureFile() const;
        private:
            std::string _mapImage;
            std::string _texturePath;
            bool _initialised = false;
            Texture2D _cubicmap;
            Texture2D _texture;
            Vector3 _position;
            Model _model;
            Image _image;
            Mesh _mesh;
            Color *_pixels;
    };
}

#endif /* !MAP_HPP_ */
