/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** Event.hpp
*/

#ifndef EVENT_HPP_
#define EVENT_HPP_

#include "raylib.h"
#include "GamePad/GamePad.hpp"

namespace RaylibEvent {
    /**
     * @brief class for handle user event, as keyboard inputs
     * 
     */
    class Event {
        public:
            /**
             * @brief Construct a new Event object
             * 
             */
            Event();

            /**
             * @brief Destroy the Event object
             * 
             */
            ~Event();

            /**
             * @brief Get the Key Input object
             * 
             * @return int 
             */
            int getKeyInput() const;

            /**
             * @brief return true if mouse is on given rectangle
             * 
             * @param x 
             * @param y 
             * @param a 
             * @param b 
             * @return true 
             * @return false 
             */
            bool mouseOnText(const float x, const float y, const float a, const float b);

            /**
             * @brief if the given key is press, return true
             * 
             * @param key 
             * @return true 
             * @return false 
             */
            bool isKeyDown(const int key);
            /**
             * @brief 
             * 
             * @param key 
             * @return true 
             * @return false 
             */
            bool isKeyReleased(const int key);
    };
}

#endif /* !EVENT_HPP_ */
