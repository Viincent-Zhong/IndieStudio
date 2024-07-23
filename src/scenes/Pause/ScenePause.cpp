/*
** EPITECH PROJECT, 2022
** Project Indie stduio
** File description:
** ScenePause.cpp
*/

#include <iostream>
#include "ScenePause.hpp"
#include "Parser.hpp"

ScenePause::ScenePause(IndieStudio::IGraphical &lib) : _id(PAUSE)
{
    Parser parser(INIT_PATH);

    _path.pathButtonExit = parser.getDataFromFile("BUTTONEXIT");
    _path.pathButtonExitHover = parser.getDataFromFile("BUTTONEXITHOVER");
    _path.pathButtonResume = parser.getDataFromFile("BUTTONRESUME");
    _path.pathButtonResumeHover = parser.getDataFromFile("BUTTONRESUMEHOVER");
    _path.pathButtonSaveAndQuit = parser.getDataFromFile("BUTTONSAVE");
    _path.pathButtonSaveAndQuitHover = parser.getDataFromFile("BUTTONSAVEHOVER");
    _path.pathButtonParams = parser.getDataFromFile("BUTTONPARAMS");
    _path.pathButtonParamsHover = parser.getDataFromFile("BUTTONPARAMSHOVER");
    _path.pathButtonBack = parser.getDataFromFile("BUTTONBACK");
    _path.pathButtonBackHover = parser.getDataFromFile("BUTTONBACKHOVER");
    _path.music = parser.getDataFromFile("MUSIC");
    _path.background = parser.getDataFromFile("BACKGROUND");
    _path.btnSound = parser.getDataFromFile("BTN_SOUND");
    for (int i = 0; i != 5; ++i)
        _buttons.push_back(std::make_unique<RaylibButton::Button>());
    std::pair<int, int> windowSize = lib.getWindowSize();
    _buttons.at(0)->create(_path.pathButtonExit, _path.pathButtonExitHover, {windowSize.first / 3.84, windowSize.second / 1.44}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(1)->create(_path.pathButtonResume, _path.pathButtonResumeHover, {windowSize.first / 2.56, windowSize.second / 7.2}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(2)->create(_path.pathButtonSaveAndQuit, _path.pathButtonSaveAndQuitHover, {windowSize.first / 1.92, windowSize.second / 1.44}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(3)->create(_path.pathButtonParams, _path.pathButtonParamsHover, {windowSize.first / 2.56, windowSize.second / 3.08571429}, _path.btnSound, lib.getEffectLevel());
    _buttons.at(4)->create(_path.pathButtonBack, _path.pathButtonBackHover, {windowSize.first / 2.56, windowSize.second / 1.96363636}, _path.btnSound, lib.getEffectLevel());
}

ScenePause::~ScenePause()
{
}

std::pair<IndieStudio::IScene::SceneId, bool> ScenePause::run(IndieStudio::IGraphical &lib)
{
    std::pair<IndieStudio::IScene::SceneId, bool> event;

    _music.initMusic(_path.music, lib.getMusicVolume());
    _background.create(_path.background);
    for (auto &button : _buttons)
        button->setEffectLevel(lib.getEffectLevel());
    while (!lib.endGame()) {
        _music.updateMusicStream();
        event = sceneEvents(lib);
        if (event.first != _id)
            return event;
        drawElems(lib);
    }
    return {END, true};
}

void ScenePause::drawElems(IndieStudio::IGraphical &lib)
{
    lib.startDrawing(true);
    _background.display({0.0f, 0.0f}, 1.0f);
    for (auto &button : _buttons) {
        button->animation();
        button->display();
    }
    lib.endDrawing();
}

std::pair<IndieStudio::IScene::SceneId, bool> ScenePause::sceneEvents(IndieStudio::IGraphical &lib)
{
    if (_buttons.at(1)->isPress() || _gamepad.isPadKeyReleased(0, PAD_START))
        return {GAME, false};
    if (_buttons.at(0)->isPress() || _gamepad.isPadKeyReleased(0, PAD_B))
        return {END, true};
    if (_buttons.at(4)->isPress() || _gamepad.isPadKeyReleased(0, PAD_A))
        return {MENU, true};
    if (_buttons.at(2)->isPress() || _gamepad.isPadKeyDown(0, PAD_X)) {
        lib.setSave(true);
        return {GAME, false};
    }
    if (_buttons.at(3)->isPress() || _gamepad.isPadKeyReleased(0, PAD_Y))
        return {PARAMS, true};
    return {_id, true};
}

void ScenePause::initScene()
{
}
