/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneParams.hpp
*/

#ifndef SceneParams_HPP_
#define SceneParams_HPP_

#include "IScene.hpp"
#include "Text/Text.hpp"
#include "Button/Button.hpp"
#include "Music/Music.hpp"
#include "Image/Image.hpp"

#define INIT_PATH_P "src/scenes/Params/init.txt"

class SceneParams : public IndieStudio::IScene {
    typedef struct path_s {
        std::string pathButtonExit;
        std::string pathButtonExitHover;
        std::string pathButtonBack;
        std::string pathButtonBackHover;
        std::string pathButtonPlusHover;
        std::string pathButtonMinusHover;
        std::string pathButtonPlus;
        std::string pathButtonMinus;
        std::string pathButtonPlusHover2;
        std::string pathButtonMinusHover2;
        std::string pathButtonPlus2;
        std::string pathButtonMinus2;
        std::string font;
        std::string background;
        std::string music;
        std::string tuto;
        std::string btnSound;
    } path_t;

    public:
        SceneParams(IndieStudio::IGraphical &lib);
        ~SceneParams();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        void initScene();
        void initScene(IndieStudio::IGraphical &lib);
        SceneParams(SceneParams&&) = default;
        IndieStudio::IScene::SceneId sceneEvents(IndieStudio::IGraphical &lib);
        void drawElems(IndieStudio::IGraphical &lib);
        void updateFps(IndieStudio::IGraphical &lib, const int value);

    protected:
    private:
        IndieStudio::IScene::SceneId const _id;
        path_t _path;
        RaylibText::Text _text;
        std::vector<std::unique_ptr<RaylibButton::Button>> _buttons;
        RaylibImage::Image _background;
        RaylibImage::Image _doc;
        RaylibMusic::MusicA _music;
        RaylibGamePad::GamePad _gamepad;
        float _musicLevel;
        float _effectLevel;
        unsigned int _fps;
        int _soundVolume;
        int _effectVolume;
};

#endif /* !SceneParams_HPP_ */
