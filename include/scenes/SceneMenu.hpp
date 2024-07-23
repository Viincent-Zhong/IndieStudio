/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneMenu.hpp
*/

#ifndef SCENEMENU_HPP_
#define SCENEMENU_HPP_

#include <memory>
#include "IScene.hpp"
#include "Button/Button.hpp"
#include "Element/Element.hpp"
#include "Text/Text.hpp"
#include "Event/Event.hpp"
#include "GamePad/GamePad.hpp"
#include "Music/Music.hpp"
#include "Image/Image.hpp"

#define PATH_INIT_MENU  "src/scenes/Menu/init.txt"

class SceneMenu : public IndieStudio::IScene {
    typedef struct path_s {
        std::string pathButtonGame;
        std::string pathButtonGameHover;
        std::string pathButtonLoadGame;
        std::string pathButtonLoadGameHover;
        std::string pathButtonExit;
        std::string pathButtonExitHover;
        std::string pathButtonParams;
        std::string pathButtonParamsHover;
        std::string playerSkelet;
        std::string playerAnim;
        std::string playerOneTexture;
        std::string playerTwoTexture;
        std::string font;
        std::string music;
        std::string logo;
        std::string background;
        std::string btnSound;
    } path_t;

    public:
        SceneMenu(IndieStudio::IGraphical &lib);
        ~SceneMenu();
        SceneMenu(SceneMenu&&) = default;
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        IndieStudio::IScene::SceneId sceneEvents(IndieStudio::IGraphical &lib);
        void drawElems(IndieStudio::IGraphical &lib);
        void parseFile(std::string const &path);
        void initData(IndieStudio::IGraphical &lib);
        void incrementBlinkCounter();
        void resetBlinkCounter();
        int getBlinkCounter();

    protected:
    private:
        enum ButtonType {
            GAME = 0,
            EXIT = 1,
            PARAM = 2,
            LOAD = 3
        };
        IndieStudio::IScene::SceneId const _id;
        path_t _path;
        RaylibText::Text _text;
        RaylibEvent::Event _event;
        std::vector<std::unique_ptr<RaylibButton::Button>> _buttons;
        std::vector<std::unique_ptr<RaylibElement::Element>> _elems;
        RaylibMusic::MusicA _music;
        RaylibImage::Image _logo;
        RaylibImage::Image _background;
        RaylibGamePad::GamePad _gamepad;
        int _blinkCounter = 0;
};

#endif /* !SCENEMENU_HPP_ */
