/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** Element.hpp
*/

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_

#include <string>
#include "raylib.h"
#include "Map/Map.hpp"

namespace RaylibElement {
    /**
     * @brief class for handle Element as Player, bomb...
     * handle IQM files for model and animation and PNG for texture
     * 
     */
    class Element {
        public:
            /**
             * @brief Construct a new Element object
             * 
             */
            Element();

            /**
             * @brief Construct a new Element object
             * 
             * @param elemName 
             * @param pos 
             * @param model 
             * @param texture 
             * @param animation 
             */
            Element(std::string const &elemName, std::pair<float, float> const &pos,
                std::string const &model, std::string const &texture, std::string const &animation);

            /**
             * @brief Destroy the Element object
             * 
             */
            ~Element();

            /**
             * @brief construct new Element object, as the constructor
             * 
             * @param elemName 
             * @param pos 
             * @param model 
             * @param texture 
             * @param animation 
             */
            void create(std::string const &elemName, std::pair<float, float> const &pos,
                std::string const &model, std::string const &texture, std::string const &animation);

            /**
             * @brief draw Element at given positon X Y
             * 
             * @param pos 
             */
            void displayAtPos(std::pair<float, float> const &pos);

            /**
             * @brief draw Element at his position
             * 
             */
            void display() const;

            /**
             * @brief anim Elemen (exemple: player walk)
             * 
             */
            void anim();

            /**
             * @brief verif if the Element can move and move it
             * 
             * @param move direction of the Element
             * @param map the map, for have all wall not destructible
             * @return true can move
             * @return false cannot move
             */
            bool move(std::pair<float, float> const &move, RaylibMap::Map const &map);

            /**
             * @brief check collision of the Element with another Element
             * 
             * @param elem other Element
             * @return true collision
             * @return false no collision
             */
            bool checkCollision(Element &elem);

            /**
             * @brief change dircetion of the Element
             * 
             * @param move 
             */
            void changeDirection(std::pair<float, float> const &move);

            /**
             * @brief Set the Elem Size object
             * 
             * @param x 
             * @param y 
             * @param z 
             */
            void setElemSize(const float x, const float y, const float z);

            /**
             * @brief Set the Elem Rotation object
             * 
             * @param rotation 
             * @param x 
             * @param y 
             * @param z 
             */
            void setElemRotation(const float rotation, const float x, const float y, const float z);

            /**
             * @brief change rotation of the element in the space
             * 
             * @param path 
             */
            void updateElemTexture(std::string const &path);

            /**
             * @brief 
             * 
             * @param map 
             * @return true 
             * @return false 
             */
            bool collisionWall(RaylibMap::Map const &map);

            /**
             * @brief Set the Animation object for a specific position
             * 
             * @param anim 
             */
            void setAnimation(unsigned int const &anim);

            /**
             * @brief if Element cannot move, return to it old pos
             * 
             * @param move 
             */
            void substractMove(std::pair<float, float> const &move);

            /**
             * @brief Set the Animation Model object
             * 
             * @param id 
             */
            void setAnimationModel(const unsigned int id);

        private:
            Vector3 _position;
            Vector3 _size;
            Vector3 _rotation;
            Vector3 _scale;
            Model _model;
            ModelAnimation *_anims;
            Texture2D _texture;
            Color _color;
            unsigned int _animsCount;
            int _animFrameCounter;
            float _rotationAngle;
            bool _collision;
            unsigned int _animation;
            bool _init;
    };
}

#endif /* !ELEMENT_HPP_ */
