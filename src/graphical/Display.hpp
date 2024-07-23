/*
** EPITECH PROJECT, 2021
** idistudio
** File description:
** Display.hpp
*/

#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <map>
#include "raylib.h"
#include "raymath.h"
#include "IGraphical.hpp"

class Display : public IndieStudio::IGraphical {
    public:
        Display(unsigned int const screenWidth, unsigned int const screenHeight, std::string const &windowName, unsigned int const fps);
        ~Display();
        void setFps(unsigned int const &fps);
        void startDrawing(const bool refresh) const;
        void endDrawing() const;
        void start3d() const;
        void end3d() const;
        bool endGame();
        void resizeWindow();
        float getFrameTime();
        float getMusicVolume() const;
        void setMusicVolume(const float volume);
        std::pair<int, int> getWindowSize() const;
        void setLoadGame(const bool load);
        bool getLoad() const;
        void setSave(const bool save);
        bool getSave() const;
        float getEffectLevel() const;
        void setEffectLevel(const float level);

    protected:
    private:
        unsigned int _screenWidth;
        unsigned int _screenHeight;
        Camera3D _camera;
        float _musicVolume;
        float _effectLevel;
        bool _loadGame;
        bool _saveGame;

};

#endif /* !DISPLAY_HPP_ */
