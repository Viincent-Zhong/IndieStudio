/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** ScenePause.hpp
*/

#ifndef SCENEPAUSE_HPP_
#define SCENEPAUSE_HPP_

#include "Button/Button.hpp"
#include "Music/Music.hpp"
#include "Image/Image.hpp"
#include "IScene.hpp"

#define INIT_PATH "src/scenes/Pause/init.txt"

class ScenePause : public IndieStudio::IScene {
    typedef struct path_s {
        std::string pathButtonExit;
        std::string pathButtonExitHover;
        std::string pathButtonResume;
        std::string pathButtonResumeHover;
        std::string pathButtonSaveAndQuit;
        std::string pathButtonSaveAndQuitHover;
        std::string pathButtonParams;
        std::string pathButtonParamsHover;
        std::string pathButtonBack;
        std::string pathButtonBackHover;
        std::string music;
        std::string background;
        std::string btnSound;
    } path_t;

    public:
        ScenePause(IndieStudio::IGraphical &lib);
        ~ScenePause();
        ScenePause(ScenePause&&) = default;
        std::pair<IndieStudio::IScene::SceneId, bool> sceneEvents(IndieStudio::IGraphical &lib);
        void drawElems(IndieStudio::IGraphical &lib);
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);

    protected:
    private:
        IndieStudio::IScene::SceneId const _id;
        path_t _path;
        std::vector<std::unique_ptr<RaylibButton::Button>> _buttons;
        RaylibMusic::MusicA _music;
        RaylibImage::Image _background;
        RaylibGamePad::GamePad _gamepad;
};

#endif /* !SCENEPAUSE_HPP_ */
