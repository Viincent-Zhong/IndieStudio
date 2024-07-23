/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneRecap.hpp
*/

#ifndef SCENERECAP_HPP_
#define SCENERECAP_HPP_

#include "IScene.hpp"
#include "Element/Element.hpp"
#include "Button/Button.hpp"
#include "Music/Music.hpp"
#include "Text/Text.hpp"
#include "Image/Image.hpp"

#define FILE_PATH   "src/scenes/Recap/init.txt"
#define ANIM_WIN    3
#define ANIM_LOSE   5
#define BTN_QUIT    0
#define BTN_HOME    1

class SceneRecap : public IndieStudio::IScene {
    public:
        SceneRecap(IndieStudio::IGraphical &lib);
        ~SceneRecap();
        SceneRecap(SceneRecap&&) = default;
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        IndieStudio::IScene::SceneId sceneEvents();
        void drawElems(IndieStudio::IGraphical &lib);
        void getDataGame(IndieStudio::IGraphical &lib);

    protected:
    private:
        typedef struct path_s {
            std::string music;
            std::string font;
            std::string file;
            std::string btnExit;
            std::string btnExitHovered;
            std::string btnGame;
            std::string btnGameHovered;
            std::string model;
            std::string anim;
            std::string background;
            std::string btnSound;
        } path_t;
        path_t _paths;
        IndieStudio::recapParams _gameRecap;
        IndieStudio::IScene::SceneId const _id;
        std::vector<std::unique_ptr<RaylibElement::Element>> _elems;
        std::vector<std::unique_ptr<RaylibButton::Button>> _buttons;
        RaylibMusic::MusicA _music;
        RaylibText::Text _text;
        RaylibImage::Image _background;
        RaylibGamePad::GamePad _gamepad;
};

#endif /* !SCENERECAP_HPP_ */
