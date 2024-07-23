/*
** EPITECH PROJECT, 2022
** Project indie studio
** File description:
** GamePad.hpp
*/

#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_

enum PadKey {
    PAD_UP,
    PAD_DOWN,
    PAD_LEFT,
    PAD_RIGHT,
    PAD_START,
    PAD_SELECT,
    PAD_X,
    PAD_Y,
    PAD_A,
    PAD_B,
    PAD_TRIGGER_LEFT,
    PAD_TRIGGER_RIGHT,
    PAD_NOTHING
};

namespace RaylibGamePad {
    class GamePad {
        public :
        GamePad();
        ~GamePad();
        bool isTouchDown(const int gamepad, const int key);
        bool isPadKeyDown(const int gamepad, PadKey key);
        bool isPadKeyReleased(const int gamepad, PadKey key);
        int getTouchPress(const int gamepad);
        bool gamePadExist(const int gamepad);
        PadKey getPadKeyDown(const int gamepad);
        PadKey getPadKeyPressed(const int gamepad);
        PadKey getPadKeyReleased(const int gamepad);
    };
}

#endif /* !GAMEPAD_HPP_ */
