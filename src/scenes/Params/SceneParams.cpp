/*
** EPITECH PROJECT, 2022
** Project Indie stduio
** File description:
** SceneParams.cpp
*/

#include <iostream>
#include "SceneParams.hpp"
#include "Parser.hpp"

SceneParams::SceneParams(IndieStudio::IGraphical &lib) : _id(PARAMS), _soundVolume(100), _musicLevel(1.0f), _fps(30), _effectVolume(100), _effectLevel(1.0f)
{
    Parser parser(INIT_PATH_P);

    _path.pathButtonExit = parser.getDataFromFile("BUTTONEXIT");
    _path.pathButtonExitHover = parser.getDataFromFile("BUTTONEXITHOVER");
    _path.pathButtonBack = parser.getDataFromFile("BUTTONBACK");
    _path.pathButtonBackHover = parser.getDataFromFile("BUTTONBACKHOVER");
    _path.font = parser.getDataFromFile("FONT");
    _path.pathButtonMinus = parser.getDataFromFile("BUTTONMINUS");
    _path.pathButtonMinusHover = parser.getDataFromFile("BUTTONMINUSHOVER");
    _path.pathButtonPlus = parser.getDataFromFile("BUTTONPLUS");
    _path.pathButtonPlusHover = parser.getDataFromFile("BUTTONPLUSHOVER");
    _path.background = parser.getDataFromFile("BACKGROUND");
    _path.music = parser.getDataFromFile("MUSIC");
    _path.tuto = parser.getDataFromFile("DOC");
    _path.btnSound = parser.getDataFromFile("BTN_SOUND");
    for (int i = 0; i != 8; ++i)
        _buttons.push_back(std::make_unique<RaylibButton::Button>());
    // 1920 * 1080
    std::pair<int, int> windowSize = lib.getWindowSize();
    _buttons.at(0)->create(_path.pathButtonBack, _path.pathButtonBackHover, {windowSize.first / 1.3241, windowSize.second / 1.2}, _path.btnSound, _effectLevel);
    _buttons.at(1)->create(_path.pathButtonExit, _path.pathButtonExitHover, {windowSize.first / 38.4, windowSize.second / 1.2}, _path.btnSound, _effectLevel);
    _buttons.at(2)->create(_path.pathButtonMinus, _path.pathButtonMinusHover, {windowSize.first / 5.84, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
    _buttons.at(3)->create(_path.pathButtonPlus, _path.pathButtonPlusHover, {windowSize.first / 200.6, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
    _buttons.at(4)->create(_path.pathButtonMinus, _path.pathButtonMinusHover, {windowSize.first / 1.07, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
    _buttons.at(5)->create(_path.pathButtonPlus, _path.pathButtonPlusHover, {windowSize.first / 1.3, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
    _buttons.at(6)->create(_path.pathButtonMinus, _path.pathButtonMinusHover, {windowSize.first / 1.7, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
    _buttons.at(7)->create(_path.pathButtonPlus, _path.pathButtonPlusHover, {windowSize.first / 2.4, windowSize.second / 2.16}, _path.btnSound, _effectLevel);
}

IndieStudio::IScene::SceneId SceneParams::sceneEvents(IndieStudio::IGraphical &lib)
{
    if (_buttons.at(1)->isPress() || _gamepad.isPadKeyReleased(0, PAD_B))
        return END;
    if (_buttons.at(0)->isPress() || _gamepad.isPadKeyReleased(0, PAD_A))
        return MENU;
    if (_buttons.at(2)->isPress() || _gamepad.isPadKeyReleased(0, PAD_DOWN) && _fps > 10)
        updateFps(lib, -5);
    if (_buttons.at(3)->isPress() || _gamepad.isPadKeyReleased(0, PAD_UP) && _fps < 120)
        updateFps(lib, 5);
    if (_buttons.at(4)->isPress() || _gamepad.isPadKeyReleased(0, PAD_LEFT)) {
        _soundVolume -= 10;
        _musicLevel -= 0.10f;
        if (_musicLevel < 0.0f) {
            _soundVolume = 0;
            _musicLevel = 0.0f;
        }
        _music.setMusicVolume(_musicLevel);
        lib.setMusicVolume(_musicLevel);
    }
    if (_buttons.at(5)->isPress() || _gamepad.isPadKeyReleased(0, PAD_RIGHT)) {
        _soundVolume += 10;
        _musicLevel += 0.10f;
        if (_musicLevel > 1.0f) {
            _musicLevel = 1.0f;
            _soundVolume = 100;
        }
        _music.setMusicVolume(_musicLevel);
        lib.setMusicVolume(_musicLevel);
    }
    if (_buttons.at(6)->isPress() || _gamepad.isPadKeyReleased(0, PAD_LEFT)) {
        _effectVolume -= 10;
        _effectLevel -= 0.10f;
        if (_effectVolume < 0.0f) {
            _effectVolume = 0;
            _effectLevel = 0.0f;
        }
        for (auto &button : _buttons)
            button->setEffectLevel(_effectLevel);
        lib.setEffectLevel(_effectLevel);
    }
    if (_buttons.at(7)->isPress() || _gamepad.isPadKeyReleased(0, PAD_RIGHT)) {
        _effectVolume += 10;
        _effectLevel += 0.10f;
        if (_effectVolume > 100.0f) {
            _effectVolume = 100.0f;
            _effectLevel = 1.0f;
        }
        for (auto &button : _buttons)
            button->setEffectLevel(_effectLevel);
        lib.setEffectLevel(_effectLevel);
    }
    return _id;
}

SceneParams::~SceneParams()
{
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneParams::run(IndieStudio::IGraphical &lib)
{
    IndieStudio::IScene::SceneId event;

    initScene(lib);
    while (!lib.endGame()) {
        _music.updateMusicStream();
        event = sceneEvents(lib);
        if (event != _id)
            return {event, true};
        drawElems(lib);
    }
    return {END, true};
}

void SceneParams::initScene()
{
}

void SceneParams::updateFps(IndieStudio::IGraphical &lib, const int value)
{
    _fps += value;
    lib.setFps(_fps);
}

void SceneParams::initScene(IndieStudio::IGraphical &lib)
{
    _text.loadFont(_path.font);
    _music.initMusic(_path.music, lib.getMusicVolume());
    _background.create(_path.background);
    _doc.create(_path.tuto);
}

void SceneParams::drawElems(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    
    lib.startDrawing(true);
    _background.display({0.0f, 0.0f}, 1.0f);
    _text.printText("PARAMS", {windowSize.first / 2.4, windowSize.second / 27}, BLACK, 9.0f);
    _text.printText("FPS", {windowSize.first / 15.4, windowSize.second / 3.6}, RED, 9.0f);
    _text.printText(std::to_string(_fps), {windowSize.first / 15.907, windowSize.second / 2.10}, WHITE, 10.0f);
    _text.printText("SOUND", {windowSize.first / 1.3, windowSize.second / 3.6}, RED, 9.0f);
    _text.printText(std::to_string(_soundVolume), {windowSize.first / 1.2, windowSize.second / 2.10}, WHITE, 10.0f);
    _text.printText("EFFECT", {windowSize.first / 2.4, windowSize.second / 3.6}, RED, 9.0f);
    _text.printText(std::to_string(_effectVolume), {windowSize.first / 2.1, windowSize.second / 2.10}, WHITE, 10.0f);
    for (auto &button : _buttons) {
        button->animation();
        button->display();
    }
    _doc.display({windowSize.first / 2.7428, windowSize.second / 1.5428}, 0.30f);
    lib.endDrawing();
}
