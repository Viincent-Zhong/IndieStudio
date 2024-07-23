/*
** EPITECH PROJECT, 2022
** Project Indie studio
** File description:
** SceneSelection.hpp
*/

#ifndef SCENESELECTION_HPP_
#define SCENESELECTION_HPP_

#include <memory>
#include <map>
#include "IEntity.hpp"
#include "IScene.hpp"
#include "Button/Button.hpp"
#include "Text/Text.hpp"
#include "Event/Event.hpp"
#include "Music/Music.hpp"
#include "Image/Image.hpp"

#define NAME_SIZE   20
#define DELETE      259

class SceneSelection : public IndieStudio::IScene {
    typedef struct path_s {
        std::string playerSkelet;
        std::string playerAnim;
        std::vector<std::string> buttons;
        std::vector<std::string> texture;
        std::vector<std::string> map;
        std::string font;
        std::string music;
        std::string background;
        std::string btnSound;
    } path_t;

    typedef struct game_param_s {
        bool againstAi;
        bool bonus;
        std::string map;
        std::string playerOneName;
        std::string playerTwoName;
        std::string texture_one;
        std::string texture_two;
    } game_param_t;

    public:
        SceneSelection(IndieStudio::IGraphical &lib);
        SceneSelection(SceneSelection&&) = default;
        ~SceneSelection();
        void initScene();
        std::pair<IndieStudio::IScene::SceneId, bool> run(IndieStudio::IGraphical &lib);
        void drawElems(IndieStudio::IGraphical &lib);
        IndieStudio::IScene::SceneId sceneEvents(IndieStudio::IGraphical &lib);
        bool conditionEnd(IndieStudio::IGraphical &lib);
        void getPath(std::string const &file);
        void initButtons(IndieStudio::IGraphical &lib);
        void initElems(IndieStudio::IGraphical &lib);
        void printStatusParams(IndieStudio::IGraphical &lib);
        void handleButtonCheckBox(IndieStudio::IGraphical &lib, bool &status, const unsigned int id, std::pair<float, float> const &pos);
        void textInput(IndieStudio::IGraphical &lib, std::string &input, const int keyInput, std::vector<float> const &rec);
        void updateSkin(IndieStudio::IGraphical &lib, const int incr, const int max, const int min, const unsigned int idButton, const unsigned int id);

    protected:
    private:
        void saveParams();
        enum ButtonType {
            STARTGAME = 0,
            COLORUPONE = 1,
            COLORDOWNONE = 2,
            COLORUPTWO = 3,
            COLORDOWNTWO = 4,
            BACK = 5,
            AI = 6,
            BONUS = 7,
            SIZEUP = 8,
            SIZEDOWN = 9
        };
        game_param_t _gameParam;
        path_t _path;
        IndieStudio::IScene::SceneId const _id;
        std::vector<std::string> _elemName;
        std::map<std::string, int> _textureElem;
        RaylibText::Text _text;
        RaylibEvent::Event _event;
        std::vector<std::unique_ptr<RaylibElement::Element>> _elems;
        std::vector<std::unique_ptr<RaylibButton::Button>> _buttons;
        RaylibMusic::MusicA _music;
        std::vector<std::unique_ptr<RaylibImage::Image>> _map;
        unsigned int _indexMap;
        RaylibImage::Image _background;
        RaylibGamePad::GamePad _gamepad;
};

#endif /* !SCENESELECTION_HPP_ */
