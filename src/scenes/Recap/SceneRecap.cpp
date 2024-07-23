/*
** EPITECH PROJECT, 2022
** Project Indie stduio
** File description:
** SceneRecap.cpp
*/

#include <string.h>
#include <iostream>
#include "Parser.hpp"
#include "IOBinary.hpp"
#include "SceneRecap.hpp"

SceneRecap::SceneRecap(IndieStudio::IGraphical &lib) : _id(RECAP)
{
    Parser parser(FILE_PATH);

    _paths.anim = parser.getDataFromFile("ANIM");
    _paths.btnExit = parser.getDataFromFile("BUTTONEXIT");
    _paths.btnExitHovered = parser.getDataFromFile("BUTTONEXITHOVER");
    _paths.btnGame = parser.getDataFromFile("BUTTONGAME");
    _paths.btnGameHovered = parser.getDataFromFile("BUTTONGAMEHOVER");
    _paths.file = parser.getDataFromFile("FILE");
    _paths.font = parser.getDataFromFile("FONT");
    _paths.model = parser.getDataFromFile("MODEL");
    _paths.music = parser.getDataFromFile("MUSIC");
    _paths.background = parser.getDataFromFile("BACKGROUND");
    _paths.btnSound = parser.getDataFromFile("BTN_SOUND");
    _gameRecap = {0};
    for (int i = 0; i != 2; ++i)
        _buttons.push_back(std::make_unique<RaylibButton::Button>());
    std::pair<int, int> windowSize = lib.getWindowSize();
    _buttons.at(BTN_QUIT)->create(_paths.btnExit, _paths.btnExitHovered, {windowSize.first / 48, windowSize.second / 21.6}, _paths.btnSound, lib.getEffectLevel());
    _buttons.at(BTN_HOME)->create(_paths.btnGame, _paths.btnGameHovered, {windowSize.first / 1.28, windowSize.second / 21.6}, _paths.btnSound, lib.getEffectLevel());
}

SceneRecap::~SceneRecap()
{
}

std::pair<IndieStudio::IScene::SceneId, bool> SceneRecap::run(IndieStudio::IGraphical &lib)
{
    _gameRecap = IOBinary::readFile<IndieStudio::recapParams>(_paths.file);
    remove(_paths.file.c_str());
    IndieStudio::IScene::SceneId event;

    if (_elems.size() < 2)
        getDataGame(lib);
    _music.initMusic(_paths.music, lib.getMusicVolume());
    _text.loadFont(_paths.font);
    for (auto &button : _buttons)
        button->setEffectLevel(lib.getEffectLevel());
    while (!lib.endGame()) {
        _music.updateMusicStream();
        event = this->sceneEvents();
        if (event != this->_id)
            return {event, true};
        drawElems(lib);
    }
    return {END, true};
}

void SceneRecap::initScene()
{
    for (auto it = _elems.begin(); it != _elems.end();)
        it = _elems.erase(it);
}

IndieStudio::IScene::SceneId SceneRecap::sceneEvents()
{
    if (_buttons.at(BTN_QUIT)->isPress() || _gamepad.isPadKeyReleased(0, PAD_B))
        return END;
    if (_buttons.at(BTN_HOME)->isPress() || _gamepad.isPadKeyReleased(0, PAD_A))
        return MENU;
    return _id;
}

void SceneRecap::drawElems(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    std::vector<std::pair<float, float>> posNames = {{windowSize.first / 15, windowSize.second / 1.35}, {(windowSize.first / 3.28), windowSize.second / 1.35}, {(windowSize.first / 1.64), windowSize.second / 1.35}, {(windowSize.first / 1.23), windowSize.second / 1.35}};
    lib.startDrawing(true);
    _background.display({0.0f, 0.0f}, 1.0f);
    lib.start3d();
    for (auto &elem : _elems) {
        elem->anim();
        elem->display();
    }
    lib.end3d();
    for (auto &button : _buttons) {
        button->animation();
        button->display();
    }
    for (int i = 0; i != _gameRecap.nbrPlayers; ++i)
        _text.printText(_gameRecap.players[i].playerName, posNames.at(i), BLUE, 5.0f);
    lib.endDrawing();
}

void SceneRecap::getDataGame(IndieStudio::IGraphical &lib)
{
    std::pair<int, int> windowSize = lib.getWindowSize();
    const std::vector<std::pair<float, float>> posElems = {{windowSize.first / -(128.0f), windowSize.second / 360}, {windowSize.first / -(384.0f), windowSize.second / 360}, {windowSize.first / 384.0f, windowSize.second / 360}, {windowSize.first / 128, windowSize.second / 360}};

    for (int i = 0; i != _gameRecap.nbrPlayers; ++i) {
        _elems.push_back(std::make_unique<RaylibElement::Element>());
        _elems.back()->create(_gameRecap.players[i].playerName, posElems.at(i), _paths.model, _gameRecap.players[i].playerTexture, _paths.anim);
    }
    for (int i = 0; i != _gameRecap.nbrPlayers; ++i) {
        _elems.at(i)->setElemRotation(-90.0f, 90.0f, -180.0f, 90.0f);
        if (i == _gameRecap.winner) {
            _elems.at(i)->setElemSize(7.0f, 7.0f, 7.0f);
            _elems.at(i)->setAnimationModel(ANIM_WIN);
        } else {
            _elems.at(i)->setElemSize(2.0f, 2.0f, 2.0f);
            _elems.at(i)->setAnimationModel(ANIM_LOSE);
        }
    }
    _background.create(_paths.background);
}
